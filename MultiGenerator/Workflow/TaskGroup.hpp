/**
 * @file MultiGenerator/Workflow/TaskGroup.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief A class which stores a group of tasks.
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <optional>

#include <MultiGenerator/Workflow/Task.hpp>

namespace MultiGenerator::Workflow {
    /**
     * @brief A structure which stores the task ID & its constructor.
     * 
     */
    struct TaskEntry {
        int id;
        std::function<std::unique_ptr<Task>()> constructor;

        TaskEntry(int id, std::function<std::unique_ptr<Task>()> constructor) :
            id(id),
            constructor(std::move(constructor)) {}

        ~TaskEntry() {}
    };

    /**
     * @brief A class which stores a group of tasks.
     * 
     */
    class TaskGroup {
    public:
        TaskGroup(std::shared_ptr<Variable::Argument> arg) :
            current(0),
            entry(),
            arg(std::move(arg)) {}

        TaskGroup(const TaskGroup &) = default;

        TaskGroup &operator=(const TaskGroup &) = default;

        TaskGroup(TaskGroup &&) = default;

        TaskGroup &operator=(TaskGroup &&) = default;

        ~TaskGroup() {}

        /**
         * @brief Add a task
         * 
         * @param constructor the constructor of the task
         * @return the id of this task in this TaskGroup
         */
        int add(std::function<std::unique_ptr<Task>()> constructor) {
            int id = static_cast<int>(entry.size());

            auto cont = [](const auto &cont, std::shared_ptr<Variable::Argument> arg) {
                auto task = cont();
                task->setArgument(arg);
                return task;
            };
            
            entry.emplace_back(id, std::bind(cont, std::move(constructor), arg));
            
            return id;
        }

        /**
         * @brief Get the next task to be executed. Return std::nullopt if all tasks
         * have finished.
         *
         * @return the next task or std::nullopt
         */
        std::optional<TaskEntry> next() const {
            if (current == static_cast<int>(entry.size()))
                return std::nullopt;

            return entry[current++];
        }
    private:
        mutable int current;
        std::vector<TaskEntry> entry;
        std::shared_ptr<Variable::Argument> arg;
    };
} // namespace MultiGenerator::Workflow
