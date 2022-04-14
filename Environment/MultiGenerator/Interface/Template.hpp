/**
 * @file MultiGenerator/Interface/Template.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief Some generator templates.
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <vector>

#include <MultiGenerator/Context/Environment.hpp>
#include <MultiGenerator/Executor/TaskExecutor.hpp>
#include <MultiGenerator/Workflow/TaskGroup.hpp>
#include <MultiGenerator/Interface/Component.hpp>
#include <MultiGenerator/Interface/Utility.hpp>

namespace MultiGenerator::Interface {
    class Template {
    public:
        Template(const std::string &problemName) :
            problemName(problemName),
            groups() {}
        
        ~Template() {}

        void execute(int parallelCount) {
            Executor::TaskExecutor executor;
            executor.execute(groups, parallelCount);
        }
    protected:
        void addTaskGroup(Workflow::TaskGroup group) {
            groups.push_back(std::move(group));
        }
    protected:
        std::string problemName;
    private:
        std::vector<Workflow::TaskGroup> groups;
    };

    class NormalTemplate : public Template {
    public:
        NormalTemplate(const std::string &problemName) :
            Template(problemName) {}

        template <typename Generator, typename Solution>
        void add(std::shared_ptr<Variable::Argument> arg) {
            static_assert(std::is_base_of_v<GeneratingTask, Generator>,
                "Generator must be a derived class of GeneratingTask");
            static_assert(std::is_base_of_v<SolutionTask, Solution>,
                "Solution must be a derived class of SolutionTask");

            Workflow::TaskGroup group(arg);
            group.add([arg, problemName = this->problemName]() -> std::unique_ptr<Workflow::Task> {
                auto ptr = std::make_unique<Generator>();
                ptr->setProblemName(problemName);
                return ptr;
            });
            group.add([arg, problemName = this->problemName]() -> std::unique_ptr<Workflow::Task> {
                auto ptr = std::make_unique<Solution>();
                ptr->setProblemName(problemName);
                return ptr;
            });
            addTaskGroup(std::move(group));
        }
    };

    class IntegratedTemplate : public Template {
    public:
        IntegratedTemplate(const std::string &problemName) :
            Template(problemName) {}

        template <typename IntegratedGenerator>
        void add(std::shared_ptr<Variable::Argument> arg) {
            static_assert(std::is_base_of_v<IntegratedGeneratingTask, IntegratedGenerator>,
                "IntegratedGenerator must be a derived class of IntegratedGeneratingTask");

            Workflow::TaskGroup group(arg);
            group.add([arg, problemName = this->problemName]() -> std::unique_ptr<Workflow::Task> {
                auto ptr = std::make_unique<IntegratedGeneratingTask>();
                ptr->setProblemName(problemName);
                return ptr;
            });
            addTaskGroup(std::move(group));
        }
    };
} // namespace MultiGenerator::Interface