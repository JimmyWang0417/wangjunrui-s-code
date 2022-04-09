/**
 * @file MultiGenerator/Workflow/Task.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief A abstract base class of all task classes.
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <memory>

#include <MultiGenerator/Workflow/Callable.hpp>
#include <MultiGenerator/Variable/Argument.hpp>

namespace MultiGenerator::Workflow {
    /**
     * @brief A abstract base class of all task classes.
     * 
     */
    class Task : public Callable {
    public:
        Task() :
            arg() {}

        ~Task() {}

        virtual void setArgument(std::shared_ptr<Variable::Argument> arg) {
            this->arg = std::move(arg);
        }
    protected:
        std::shared_ptr<Variable::Argument> arg;
    };
} // namespace MultiGenerator::Workflow
