/**
 * @file MultiGenerator/Workflow/Callable.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief This file declares the common interface of all callable objects.
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <memory>
#include <functional>

namespace MultiGenerator::Workflow {
    /**
     * @brief A interface of all callable classes.
     * 
     */
    class Callable {
    public:
        Callable() {}

        virtual ~Callable() {}

        virtual void call() = 0;
    };

    /**
     * @brief A wrapper of Callable which can call another function after call().
     * 
     */
    class AfterCallableWrapper : public Callable {
    public:
        AfterCallableWrapper(std::unique_ptr<Callable> callable, std::function<void()> after) :
            Callable(),
            callable(std::move(callable)),
            after(after) {}

        ~AfterCallableWrapper() {}

        void call() override {
            callable->call();
            after();
        }
    private:
        std::unique_ptr<Callable> callable;
        std::function<void()> after;
    };
} // namespace MultiGenerator::Workflow
