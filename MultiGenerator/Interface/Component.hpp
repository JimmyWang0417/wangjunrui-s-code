/**
 * @file MultiGenerator/Interface/Component.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief Some predefined components for the tasks of generating data.
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>

#include <MultiGenerator/Variable/Argument.hpp>
#include <MultiGenerator/Workflow/Task.hpp>
#include <MultiGenerator/Context/Environment.hpp>

namespace MultiGenerator::Interface {
    /**
     * @brief A task class for executing a generator program.
     * 
     */
    class GeneratingTask : public Workflow::Task {
    public:
        GeneratingTask() :
            Workflow::Task(),
            problemName(),
            inputFile() {}

        ~GeneratingTask() {}

        void setProblemName(const std::string &problemName) {
            this->problemName = problemName;
        }

        void setArgument(std::shared_ptr<Variable::Argument> arg) override {
            Workflow::Task::setArgument(std::move(arg));
            initEnvironment();
        }

        void call() override {
            generate(inputFile->getOutputStream(), arg->getConfig());
        }
    protected:
        /**
         * @brief Generate data and write data through the stream. You have
         * to implement this method to use your own generator.
         * 
         * @param data the stream of the file of the input data
         * @param config the specific configures for the generator
         */
        virtual void generate(std::ostream &data, const Variable::DataConfig &config) = 0;
    private:
        std::string problemName;
        std::unique_ptr<Context::Environment> inputFile;

        void initEnvironment() {
            inputFile = std::make_unique<Context::Environment>(
                std::unique_ptr<Context::InputStream>(),
                std::make_unique<Context::FileOutputStream>(problemName + arg->getID() + ".in")
            );
        }
    };

    /**
     * @brief A task class for executing a standard solution program.
     * 
     */
    class SolutionTask : public Workflow::Task {
    public:
        SolutionTask() :
            Workflow::Task(),
            problemName(),
            file() {}

        ~SolutionTask() {}

        void setProblemName(const std::string &problemName) {
            this->problemName = problemName;
        }

        void setArgument(std::shared_ptr<Variable::Argument> arg) override {
            Workflow::Task::setArgument(std::move(arg));
            initEnvironment();
        }

        void call() override {
            solve(file->getInputStream(), file->getOutputStream(), arg->getConfig());
        }
    protected:
        /**
         * @brief Generator the standard answer of the input file of one 
         * test case. Read data from dataIn and write the answer to dataOut.
         * You have to implement this method to use your own standard program.
         * 
         * @param dataIn the stream of the file of the input data
         * @param dataOut the stream of the file of the standard answer
         * @param config the specific configures for the generator
         */
        virtual void solve(std::istream &dataIn, std::ostream &dataOut,
            const Variable::DataConfig &config) = 0;
    private:
        std::string problemName;
        std::unique_ptr<Context::Environment> file;

        void initEnvironment() {
            file = std::make_unique<Context::Environment>(
                std::make_unique<Context::FileInputStream>(problemName + arg->getID() + ".in"),
                std::make_unique<Context::FileOutputStream>(problemName + arg->getID() + ".out")
            );
        }
    };

    /**
     * @brief A task class for executing a generator program with a solution
     * program integrated.
     * 
     */
    class IntegratedGeneratingTask : public Workflow::Task {
    public:
        IntegratedGeneratingTask() :
            Workflow::Task(),
            problemName(),
            inputFile(),
            outputFile() {}

        ~IntegratedGeneratingTask() {}

        void setProblemName(const std::string &problemName) {
            this->problemName = problemName;
        }

        void setArgument(std::shared_ptr<Variable::Argument> arg) override {
            Workflow::Task::setArgument(std::move(arg));
            initEnvironment();
        }

        void call() override {
            generate(inputFile->getOutputStream(), outputFile->getOutputStream(), arg->getConfig());
        }
    protected:
        /**
         * @brief Generate the input data and standard answer of one test
         * case in the same time. Write the input data to dadaIn and standard
         * answer to dataOut. You have to implement this method to use your
         * own generator.
         * 
         * @param dataIn the stream of the file of the input data
         * @param dataOut the stream of the file of the standard answer
         * @param config the specific configures for the generator
         */
        virtual void generate(std::ostream &dataIn, std::ostream &dataOut,
            const Variable::DataConfig &config) = 0;
    private:
        std::string problemName;
        std::unique_ptr<Context::Environment> inputFile;
        std::unique_ptr<Context::Environment> outputFile;

        void initEnvironment() {
            inputFile = std::make_unique<Context::Environment>(
                std::unique_ptr<Context::InputStream>(),
                std::make_unique<Context::FileOutputStream>(problemName + arg->getID() + ".in")
            );
            outputFile = std::make_unique<Context::Environment>(
                std::unique_ptr<Context::InputStream>(),
                std::make_unique<Context::FileOutputStream>(problemName + arg->getID() + ".out")
            );
        }
    };
} // namespace MultiGenerator::Interface
