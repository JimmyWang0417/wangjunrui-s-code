/**
 * @file MultiGenerator/Executor/Channel.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief A MPMC channel
 * @version 0.1
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <exception>
#include <memory>
#include <optional>
#include <chrono>

namespace MultiGenerator::Executor {
    /**
     * @brief A simple concurrent queue based on std::queue.
     * 
     * @tparam Element the type of the data stored by the queue
     */
    template <typename Element>
    class ConcurrentQueue {
    public:
        ConcurrentQueue() :
            que(),
            mtx() {}

        ~ConcurrentQueue() {}

        void push(const Element &element) {
            std::lock_guard<std::mutex> lock(mtx);
            que.push(element);
        }

        void push(Element &&element) {
            std::lock_guard<std::mutex> lock(mtx);
            que.push(std::move(element));
        }

        template <typename ...Args>
        void emplace(Args &&...args) {
            std::lock_guard<std::mutex> lock(mtx);
            que.emplace(std::forward<Args>(args)...);
        }

        /**
         * @brief Return the element at the front of the queue and remove it
         * from the queue.
         *
         * @return the first element when the queue is not empty; std::nullopt otherwise
         */
        std::optional<Element> pop() {
            std::lock_guard<std::mutex> lock(mtx);

            if (!que.empty()) {
                Element res = std::move(que.front());
                que.pop();
                return res;
            } else {
                return std::nullopt;
            }
        }

        bool empty() const {
            std::lock_guard lock(mtx);
            return que.empty();
        }
    private:
        std::queue<Element> que;
        mutable std::mutex mtx;
    };

    template <typename Element>
    struct ChannelData {
        ConcurrentQueue<Element> que;
        std::mutex mtx;
        std::condition_variable cond;
        std::atomic_int senderCount;

        ChannelData() :
            que(),
            mtx(),
            cond(),
            senderCount(0) {}
    };

    /**
     * @brief A handle to receive data from the channel
     * 
     * @tparam Element the type of data to receive
     */
    template <typename Element>
    class Receiver {
    public:
        Receiver() :
            channel() {}

        Receiver(std::shared_ptr<ChannelData<Element>> channel) :
            channel(channel) {}

        Receiver(const Receiver<Element> &) = delete;

        Receiver(Receiver<Element> &&) = default;

        Receiver<Element> &operator=(const Receiver<Element> &) = delete;

        Receiver<Element> &operator=(Receiver<Element> &&) = default;

        ~Receiver() {}

        int senderCount() const {
            if (!channel)
                return 0;

            return channel->senderCount;
        }

        bool hasSender() const {
            return senderCount() != 0;
        }

        int receiverCount() const {
            return channel.use_count();
        }

        bool hasReceiver() const {
            return channel.use_count() != 0;
        }

        /**
         * @brief Check whether this receiver can receive data from the channel.
         * 
         * @return true if the channel still has data inside.
         */
        bool isOpen() const {
            return hasSender() || (channel && !channel->que.empty());
        }

        /**
         * @brief Receive data from the channel. Return std::nullopt if the channel is
         * closed and there is no remain data in the queue. Keep waiting until having
         * received the data or being closed.
         *
         * @return the data from the channel or std::nullopt if it's closed
         */
        std::optional<Element> receive() {
            if (!channel)
                return std::nullopt;

            auto res = channel->que.pop();
            /** Get the reamin element first. */
            if (res.has_value())
                return res;
            else if (channel->senderCount == 0)
                return std::nullopt;
            /** res is std::nullopt here. */
            std::unique_lock<std::mutex> lock(channel->mtx);

            channel->cond.wait(lock, [&, this]() {
                res = channel->que.pop();
                return (res.has_value() || channel->senderCount == 0);
            });

            return res;
        }

        /**
         * @brief Same as receive(). Return after waiting for a duration
         * 
         * @tparam Rep template param for std::chrono::duration<Rep, Period>
         * @tparam Period template param for std::chrono::duration<Rep, Period>
         * @param dura the duration to wait for
         * @return the data from the channel or std::nullopt if it's timeout or closed
         */
        template <typename Rep, typename Period>
        std::optional<Element> receiveFor(std::chrono::duration<Rep, Period> dura) {
            if (!channel)
                return std::nullopt;

            auto res = channel->que.pop();
            /** Get the reamin element first. */
            if (res.has_value())
                return res;
            else if (channel->senderCount == 0)
                return std::nullopt;
            /** res is std::nullopt here. */
            std::unique_lock<std::mutex> lock(channel->mtx);

            channel->cond.wait_for(lock, dura, [&, this]() {
                res = channel->que.pop();
                return (res.has_value() || channel->senderCount == 0);
            });

            return res;
        }

        /**
         * @brief Same as receive(). Return after a time point.
         * 
         * @tparam Clock Template param for std::chrono::time_point<Clock, Duration>
         * @tparam Duration Template param for std::chrono::time_point<Clock, Duration>
         * @param point 
         * @return the data from the channel or std::nullopt if it's timeout or closed
         */
        template <typename Clock, typename Duration>
        std::optional<Element> receiveUntil(std::chrono::time_point<Clock, Duration> point) {
            if (!channel)
                return std::nullopt;

            auto res = channel->que.pop();
            /** Get the reamin element first. */
            if (res.has_value())
                return res;
            else if (channel->senderCount == 0)
                return std::nullopt;
            /** res is std::nullopt here. */
            std::unique_lock<std::mutex> lock(channel->mtx);

            channel->cond.wait_until(lock, point, [&, this]() {
                res = channel->que.pop();
                return (res.has_value() || channel->senderCount == 0);
            });

            return res;
        }

        std::weak_ptr<ChannelData<Element>> getHandle() const {
            return std::weak_ptr<ChannelData<Element>>(channel);
        }

        /**
         * @brief Get a receiver which gets data from the same channel.
         * 
         * @return another receiver
         */
        Receiver<Element> share() {
            return Receiver<Element>(channel);
        }

        /**
         * @brief Disconnect this receiver from the channel.
         * 
         */
        void reset() {
            channel.reset();
        }
    private:
        std::shared_ptr<ChannelData<Element>> channel;
    };

    /**
     * @brief A handle to send data through the channel
     * 
     * @tparam Element the type of data to receive
     */
    template <typename Element>
    class Sender {
    public:
        Sender() :
            channel() {}

        Sender(std::weak_ptr<ChannelData<Element>> handle) :
            channel() {
            connect(handle);
        }

        Sender(const Receiver<Element> &receiver) :
            channel() {
            connect(receiver);
        }

        Sender(const Sender<Element> &) = delete;

        Sender(Sender<Element> &&) = default;

        Sender<Element> &operator=(const Sender<Element> &) = delete;

        Sender<Element> &operator=(Sender<Element> &&) = default;

        ~Sender() {
            reset();
        }

        int senderCount() const {
            if (!hasReceiver())
                return 0;

            return channel.lock()->senderCount;
        }

        bool hasSender() const {
            return senderCount() != 0;
        }

        int receiverCount() const {
            return channel.use_count();
        }

        bool hasReceiver() const {
            return receiverCount() != 0;
        }

        /**
         * @brief Check whether there is a receiver which can receive the data
         * this sender sends.
         *
         * @return true if the channel is open
         */
        bool isOpen() const {
            return hasSender();
        }

        /**
         * @brief Send data to the channel. Return false if the channel is closed.
         *
         * @param element the data to send
         * @return false if the channel is closed
         */
        bool send(const Element &element) {
            auto ptr = channel.lock();

            if (!ptr)
                return false;

            ptr->que.push(element);
            ptr->cond.notify_one();
            return true;
        }

        void connect(std::weak_ptr<ChannelData<Element>> handle) {
            reset();
            channel = handle;
            auto ptr = channel.lock();

            if (ptr)
                ++ptr->senderCount;
        }

        /**
         * @brief Connect with a receiver.
         * 
         * @param receiver the receiver to be connected with
         */
        void connect(const Receiver<Element> &receiver) {
            connect(receiver.getHandle());
        }

        /**
         * @brief Get a sender which sends data to the same channel.
         * 
         * @return another sender
         */
        Sender<Element> share() const {
            return Sender<Element>(channel);
        }

        /**
         * @brief Disconnect from the channel.
         * 
         */
        void reset() {
            auto ptr = channel.lock();

            if (ptr) {
                --ptr->senderCount;
                ptr->cond.notify_one();
            }

            channel.reset();
        }
    private:
        std::weak_ptr<ChannelData<Element>> channel;
    };

    class InvalidChannelCountException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "InvalidChannelCountException: "
                "the count of senders or receivers must be positive.";
        }
    };

    /**
     * @brief A channel factory.
     * 
     * @tparam Element the type of data in the channel
     */
    template <typename Element>
    class Channel {
    public:
        using ChanSender = Sender<Element>;
        using ChanReceiver = Receiver<Element>;

        static std::pair<ChanSender, ChanReceiver> create() {
            ChanReceiver receiver(std::make_shared<ChannelData<Element>>());
            ChanSender sender(receiver);
            return std::make_pair(std::move(sender), std::move(receiver));
        }

        static ChanSender open(ChanReceiver &receiver) {
            if (auto handle = receiver.getHandle(); handle.expired())
                receiver = ChanReceiver(std::make_shared<ChannelData<Element>>());

            return ChanSender(receiver);
        }
    };
} // namespace MultiGenerator::Executor