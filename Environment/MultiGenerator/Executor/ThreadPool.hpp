/**
 * @file MultiGenerator/Executor/ThreadPool.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief A thread pool which execute all class derived from Runner.
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <memory>

#include <MultiGenerator/Workflow/Runner.hpp>
#include <MultiGenerator/Executor/Channel.hpp>

namespace MultiGenerator::Executor {
    /**
     * @brief A struct which stores the status and all pending runners
     * of a thread pool.
     *
     */
    struct ThreadPoolStatus {
        std::atomic_int runningWorkerCount;
        Sender<std::shared_ptr<Workflow::Runner>> runnerSender;
        Receiver<std::shared_ptr<Workflow::Runner>> runnerReceiver;

        ThreadPoolStatus() :
            runningWorkerCount(0),
            runnerSender(),
            runnerReceiver() {
            auto channel = Channel<std::shared_ptr<Workflow::Runner>>::create();
            runnerSender = std::move(channel.first);
            runnerReceiver = std::move(channel.second);
        }
    };

    /**
     * @brief The handle of the worker thread created by the thread pool.
     *
     */
    class Worker {
    public:
        Worker() :
            handle() {}

        ~Worker() {
            stop();
        }
        
        /**
         * @brief Initialize a worker thread.
         *
         * @param status the status of the thread pool
         */
        void start(ThreadPoolStatus &status) {
            handle = std::thread([&, this]() {
                status.runningWorkerCount.fetch_add(1, std::memory_order_relaxed);

                while (true) {
                    /** Get a runner from the queue or quit if it's empty. */
                    auto runner = getRunner(status);

                    if (runner)
                        runner->call();
                    else
                        break;
                }

                status.runningWorkerCount.fetch_sub(1, std::memory_order_relaxed);
            });
        }

        /**
         * @brief Wait for the worker's quitting. The worker will stop
         * automatically by itself.
         *
         */
        void stop() {
            if (handle.joinable())
                handle.join();
        }
    private:
        std::thread handle;

        std::shared_ptr<Workflow::Runner> getRunner(ThreadPoolStatus &status) {
            auto runner = status.runnerReceiver.receive();
            return runner.value_or(std::shared_ptr<Workflow::Runner>());
        }
    };

    class MaxThreadCountInvalidException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "MaxThreadCountInvalidException: The max count of threads must be positive.";
        }
    };

    class ThreadPoolAlreadyStartedException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "ThreadPoolAlreadyStartedException: The pool had already started.";
        }
    };

    class ThreadPoolAlreadyStoppedException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "ThreadPoolAlreadyStoppedException: The pool had already stopped.";
        }
    };

    class ThreadPoolIsNotRunningException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "ThreadPoolIsNotRunningException: The pool can't handle a runner when stopped.";
        }
    };

    class RunnerHandleInvalidException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "RunnerHandleInvalidException: "
                "The handle(std::shared_ptr<Workflow::Runner>) is empty.";
        }
    };

    /**
     * @brief A class which manages the workers and posts runners.
     *
     */
    class ThreadPool {
    public:
        /**
         * @brief Construct a new stopped thread pool object. Need to call start()
         * to handle tasks.
         *
         */
        ThreadPool() :
            maxWorkerCount(0),
            isStopped(true),
            status(std::make_unique<ThreadPoolStatus>()),
            workers() {}

        /**
         * @brief Construct a new thread pool object with maxWorkerCount worker(s)
         * running on the background.
         *
         * @param maxWorkerCount haw many worker(s) to create
         */
        ThreadPool(int maxWorkerCount) :
            maxWorkerCount(0),
            isStopped(true),
            status(std::make_unique<ThreadPoolStatus>()),
            workers() {
            start(maxWorkerCount);
        }

        ThreadPool(const ThreadPool &rhs) = delete;

        ThreadPool(ThreadPool &&rhs) = default;

        ThreadPool &operator=(const ThreadPool &rhs) = delete;

        ThreadPool &operator=(ThreadPool &&rhs) = default;

        ~ThreadPool() {
            if (!isStopped)
                stop();
        }

        /**
         * @brief Start the thread pool with maxWorkerCount worker(s) running
         * on the background. Throw exception when maxWorkerCount is invalid or
         * the pool has already started.
         *
         * @param maxWorkerCount haw many worker(s) to create
         */
        void start(int maxWorkerCount) {
            if (maxWorkerCount <= 0)
                throw MaxThreadCountInvalidException();

            if (!isStopped)
                throw ThreadPoolAlreadyStartedException();

            setMaxWorkerCount(maxWorkerCount);
            workers = std::vector<Worker>(static_cast<std::size_t>(maxWorkerCount));

            for (auto &worker : workers)
                worker.start(*status);

            /** Return before all workers finish initializing. */
            while (status->runningWorkerCount != maxWorkerCount)
                std::this_thread::sleep_for(std::chrono::nanoseconds(100));
        }

        /**
         * @brief Stop the thread pool after finishing all tasks in the queue.
         * Throw exception when the pool has already stopped.
         *
         */
        void stop() {
            if (isStopped)
                throw ThreadPoolAlreadyStoppedException();

            for (int i = 0; i < maxWorkerCount; ++i)
                status->runnerSender.send(std::shared_ptr<Workflow::Runner>());

            setMaxWorkerCount(0);

            /** Ensure that all workers stop first. */
            for (auto &worker : workers)
                worker.stop();
        }

        /**
         * @brief Construct a runner and put it into the queue directly.
         *
         * @tparam RunnerDerived the runner derived from Runner
         * @tparam Args the type of arguments passed to the constructor of RunnerDerived
         * @param args the arguments passed to the constructor of RunnerDerived
         * @return a handle of the runner which is able to get some essential inforamation
         */
        template <typename RunnerDerived, typename ...Args>
        std::shared_ptr<Workflow::Runner> execute(Args &&...args) {
            /** RunnerDerived must implement Runner . */
            static_assert(std::is_base_of_v<Workflow::Runner, RunnerDerived>,
                "RunnerDerived must be a derived class of Workflow::Runner.");

            auto runner = std::make_shared<RunnerDerived>(std::forward<Args>(args)...);
            execute(runner);
            return runner;
        }

        /**
         * @brief Put runner into the queue. Throw if the thread pool is stoppped
         * or the handle is empty.
         *
         * @param runner the runner handle
         */
        void execute(std::shared_ptr<Workflow::Runner> runner) {
            if (isStopped)
                throw ThreadPoolIsNotRunningException();

            if (!runner)
                throw RunnerHandleInvalidException();

            status->runnerSender.send(std::move(runner));
        }
    private:
        int maxWorkerCount;
        bool isStopped;
        std::unique_ptr<ThreadPoolStatus> status;
        std::vector<Worker> workers;

        void setMaxWorkerCount(int count) {
            maxWorkerCount = count;
            isStopped = (count == 0);
        }
    };
} // namespace MultiGenerator::Executor
