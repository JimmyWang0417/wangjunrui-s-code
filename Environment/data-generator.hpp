#pragma once

#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

namespace MultiGenerator
{

    struct Environment
    {
        enum class IOType
        {
            STDIO,
            FILE
        };
        IOType ioType;
        std::string input;
        std::string output;

        Environment() : ioType(IOType::STDIO) {}
        Environment(std::string inputFile, std::string outputFile)
            : ioType(IOType::FILE), input(inputFile), output(outputFile) {}
    };

    struct Argument
    {
        int id;

        Argument(int i = 0) : id(i) {}
    };

    struct Runner
    {
        virtual void run(std::shared_ptr<Environment> env, std::shared_ptr<Argument> args) = 0;
    };

    class Generator : public Runner
    {
    public:
        void run(std::shared_ptr<Environment> env, std::shared_ptr<Argument> args) override
        {
            if (!env || !args)
                return;

            if (env->ioType == Environment::IOType::STDIO)
            {
                generate(std::cout, std::move(args));
            }
            else
            {
                std::ofstream data(env->input);
                generate(data, std::move(args));
            }
        }

    protected:
        virtual void generate(std::ostream &data, std::shared_ptr<Argument> args) = 0;
    };

    class Solver : public Runner
    {
    public:
        void run(std::shared_ptr<Environment> env, std::shared_ptr<Argument> args) override
        {
            if (!env)
                return;

            if (env->ioType == Environment::IOType::STDIO)
            {
                solve(std::cin, std::cout, args);
            }
            else
            {
                std::ifstream dataIn(env->input);
                std::ofstream dataOut(env->output);
                solve(dataIn, dataOut, args);
            }
        }

    protected:
        virtual void solve(std::istream &dataIn, std::ostream &dataOut, std::shared_ptr<Argument> args) = 0;
    };

    struct Task
    {
        void run()
        {
            if (!generator || !solver)
                return;

            generator->run(env, args);
            solver->run(env, args);
        }

        void operator()()
        {
            run();
        }

        std::unique_ptr<Runner> generator;
        std::unique_ptr<Runner> solver;
        std::shared_ptr<Environment> env;
        std::shared_ptr<Argument> args;
    };

    template <typename G, typename S>
    std::future<void> create(const Environment &env, std::shared_ptr<Argument> arg)
    {
        Task task;
        task.generator = std::make_unique<G>();
        task.solver = std::make_unique<S>();
        task.env = std::make_shared<Environment>(env);
        task.args = arg;

        if (task.env->ioType == Environment::IOType::FILE)
        {
            auto idStr = std::to_string(arg->id);
            task.env->input += idStr + std::string(".in");
            task.env->output += idStr + std::string(".out");
        }

        auto f = std::async(std::launch::async, std::move(task));
        return f;
    }

    template <typename G, typename S>
    void exec(Environment env, std::vector<std::shared_ptr<Argument>> args, int count)
    {
        static_assert(
            std::is_base_of<Generator, G>::value && std::is_base_of<Solver, S>::value,
            "G should be a derived class of Generator and S should be a derived class of Solver.");

        std::vector<std::future<void>> futures(count);
        std::vector<bool> isRunning(count, false);
        int nowThread = 0, runningThread = 0;
        const int taskTotal = static_cast<int>(args.size());

        int tmp = 0;

        for (auto p : args)
        {
            if (!p)
            {
                std::cerr << "Argument is invalid." << std::endl;
                return;
            }

            p->id = ++tmp;
        }

        while (nowThread < taskTotal || runningThread > 0)
        {
            for (int i = 0; i < count; ++i)
            {
                if (!isRunning[i])
                {
                    if (nowThread >= taskTotal)
                        continue;

                    futures[i] = create<G, S>(env, args[nowThread]);
                    args[nowThread].reset();
                    isRunning[i] = true;
                    ++runningThread;
                    ++nowThread;
                }
                else
                {
                    std::future_status status = futures[i].wait_for(std::chrono::nanoseconds(0));

                    if (status == std::future_status::ready)
                    {
                        isRunning[i] = false;
                        --runningThread;
                    }
                }
            }
        }
    }

} // namespace MultiGenerator
