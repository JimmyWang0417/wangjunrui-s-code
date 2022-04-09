/**
 * @file MultiGenerator/Workflow/Runner.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief This file declares the abstract class of a runnable object.
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <atomic>
#include <functional>

#include <MultiGenerator/Workflow/Callable.hpp>

namespace MultiGenerator::Workflow {
    /**
     * @brief An abstract class which can only execute once in multithreading
     * environmet. Put anything according to you in derived class such as
     * the returned value or arguments.
     *
     */
    class Runner : public Callable {
    public:
        /**
         * @brief A status of one Runner.
         * 
         */
        enum class Status {
            Pending, Running, Finished
        };

        Runner() :
            status(Status::Pending) {}

        virtual ~Runner() {}

        /**
         * @brief The runner will only execute onec even though using call() more
         * than once.
         *
         */
        void call() override {
            Status oldStatus = Status::Pending;

            if (!status.compare_exchange_strong(oldStatus, Status::Running))
                return;

            run();
            status = Status::Finished;
        }

        Status getStatus() const {
            return status;
        }
    protected:
        /**
         * @brief The runner will execute run(). Implement this function in
         * the derived class in order to use your features.
         *
         */
        virtual void run() = 0;
    private:
        std::atomic<Status> status;
    };

    /**
     * @brief A class which implements lazy constructing and initializing a
     * callable object that is expensive to construct.
     *
     */
    class LazyInitRunner : public Runner {
    public:
        /**
         * @brief Get a constructor of a callable object wrapper by std::function.
         * Use this to get a callable object before being called.
         *
         * @param constructor the constructor of a callable object.
         */
        LazyInitRunner(std::function<std::unique_ptr<Callable>()> constructor) :
            constructor(std::move(constructor)),
            callable() {}

        ~LazyInitRunner() {}

        /**
         * @brief Release the ownership of the callable object. Retuen a empty
         * std::unique_ptr when the Runner doesn't finish.
         *
         * @return a std::unique_ptr of the callable object
         */
        std::unique_ptr<Callable> getCallable() {
            if (getStatus() != Status::Finished)
                return std::unique_ptr<Callable>();

            return std::move(callable);
        }
    private:
        std::function<std::unique_ptr<Callable>()> constructor;
        std::unique_ptr<Callable> callable;

        void run() override {
            callable = constructor();
            callable->call();
        }
    };
} // namespace MultiGenerator::Workflow

