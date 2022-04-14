/**
 * @file MultiGenerator/Variable/Argument.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief This file provides a method to describe the structure of test cases and
 * to be use by executor.
 * @version 0.1
 * @date 2022-03-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>
#include <vector>
#include <memory>

#include <MultiGenerator/Variable/DataConfig.hpp>

namespace MultiGenerator::Variable {
    /**
     * @brief A abstract class / interface descibing a test case including test
     * case ID & its configure.
     *
     */
    class Argument {
    public:
        Argument() : config() {}

        Argument(const DataConfig &config) :
            config(config) {}

        virtual ~Argument() {};

        /**
         * @brief Return the ID of current test case.
         *
         * @return a std::string of ID
         */
        virtual std::string getID() const = 0;

        /**
         * @brief Get the ID of an uninitialized Argument
         *
         * @return std::string of ID
         */
        virtual std::string getUninitializedID() const = 0;

        /**
         * @brief Get the config of current test case.
         *
         * @return the const ref of config
         */
        const DataConfig &getConfig() const {
            return config;
        }
    private:
        DataConfig config;
    };

    /**
     * @brief An implementation of Argument for test cases without subtasks.
     *
     */
    class NormalArgument : public Argument {
    public:
        NormalArgument() :
            Argument(),
            id(-1) {}

        NormalArgument(int id, const DataConfig &config = DataConfig()) :
            Argument(config),
            id(id) {}

        ~NormalArgument() {}

        std::string getID() const override {
            return std::to_string(id);
        }

        std::string getUninitializedID() const override {
            return std::string("-1");
        }
    private:
        int id;
    };

    /**
     * @brief Another implementation of Argument for test cases with subtasks.
     *
     */
    class SubtaskArgument : public Argument {
    public:
        SubtaskArgument() :
            Argument(),
            subtask(-1),
            id(-1) {}

        SubtaskArgument(int subtask, int id, const DataConfig &config = DataConfig()) :
            Argument(config),
            subtask(subtask),
            id(id) {}

        ~SubtaskArgument() {}

        std::string getID() const override {
            return std::to_string(subtask) + "-" + std::to_string(id);
        }

        std::string getUninitializedID() const override {
            return std::string("-1--1");
        }
    private:
        int subtask;
        int id;
    };

    /**
     * @brief A list (stack) which stores Argument.
     *
     */
    class ArgumentList {
    public:
        ArgumentList() :
            args() {}

        ~ArgumentList() {}

        /**
         * @brief Return an Argument and remove it from the list.
         *
         * @return a std::shared_ptr of the Argument
         */
        std::optional<std::shared_ptr<Argument>> next() {
            if (args.empty())
                return std::nullopt;

            auto ptr = args.back();
            args.pop_back();
            return ptr;
        }
    protected:
        std::vector<std::shared_ptr<Argument>> args;
    };

    /**
     * @brief The list which only stores NormalArgument.
     *
     */
    class NormalArgumentList : public ArgumentList {
    public:
        NormalArgumentList() :
            ArgumentList() {}

        ~NormalArgumentList() {}

        /**
         * @brief Insert a NormalArgument
         *
         * @param id the test case ID
         * @param config the data config
         */
        void insert(int id, const DataConfig &config = DataConfig()) {
            args.push_back(std::make_shared<NormalArgument>(id, config));
        }
    };

    /**
     * @brief The list which only stores SubtaskArgument.
     *
     */
    class SubtaskArgumentList : public ArgumentList {
    public:
        SubtaskArgumentList() :
            ArgumentList() {}

        ~SubtaskArgumentList() {}

        /**
         * @brief Insert a SubtaskArgument
         *
         * @param subtask the subtask ID
         * @param id the test case ID in this subtask
         * @param config the data config
         */
        void insert(int subtask, int id, const DataConfig &config = DataConfig()) {
            args.push_back(std::make_shared<SubtaskArgument>(subtask, id, config));
        }
    };
} // namespace MultiGenerator::Variable