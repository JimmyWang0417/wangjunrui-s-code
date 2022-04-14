/**
 * @file MultiGenerator/Executor/TaskExecutor.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief A executor which schedules the running of tasks.
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <memory>
#include <vector>

#include <MultiGenerator/Workflow/Runner.hpp>
#include <MultiGenerator/Workflow/Task.hpp>
#include <MultiGenerator/Workflow/TaskGroup.hpp>
#include <MultiGenerator/Executor/Channel.hpp>
#include <MultiGenerator/Executor/ThreadPool.hpp>

namespace MultiGenerator::Executor {
    /**
     * @brief A executor which schedules the running of tasks.
     * 
     */
    class TaskExecutor {
    public:
        TaskExecutor() :
            pool() {}

        ~TaskExecutor() {}

        /**
         * @brief Execute the task groups parallel. Return after all tasks have finished.
         * 
         * @param groups all tasks to be executed
         * @param parallelCount how many task can be executed at the same time
         */
        void execute(const std::vector<Workflow::TaskGroup> &groups, int parallelCount) {
            auto channel = Channel<int>::create();
            auto taskSender = std::move(channel.first);
            auto taskReceiver = std::move(channel.second);
            
            for (int i = 0; i < static_cast<int>(groups.size()); ++i)
                taskSender.send(i);

            taskSender.reset();

            pool.start(parallelCount);

            while (true) {
                auto nextGroupID = taskReceiver.receive();
                /** If all task have finished, the channel will close and return std::nullopt. */
                if (!nextGroupID.has_value())
                    break;
                /** Get the next task. */
                int id = nextGroupID.value();
                auto task = groups[id].next();
                /** All task in this task group have finished. */
                if (!task.has_value())
                    continue;

                auto sender = std::make_shared<Sender<int>>(Channel<int>::open(taskReceiver));
                auto lambda = [id, sender](auto cont) mutable {
                    /** Notify this executor to get the next task of groups[id] */
                    auto notify = [id, sender]() mutable {
                        sender->send(id);
                    };

                    std::unique_ptr<Workflow::Callable> callable = cont();
                    /** Use AfterCallableWrapper to notify the executor after task finished. */
                    return std::make_unique<Workflow::AfterCallableWrapper>(
                        std::move(callable), notify);
                };

                /** Use LazyInitRunner to create a Task object lazily to save system resource. */
                auto cont = std::bind(std::move(lambda), std::move(task.value().constructor));
                pool.execute<Workflow::LazyInitRunner>(std::move(cont));
            }

            pool.stop();
        }
    private:
        ThreadPool pool;
    };
} // namespace MultiGenerator::Executor
