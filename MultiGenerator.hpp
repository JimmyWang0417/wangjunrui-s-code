/**
 * @file MultiGenerator.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief This header is the interface of this projec. Include
 * this file to use all features.
 * @version 0.1
 * @date 2022-03-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <MultiGenerator/Context/Environment.hpp>
#include <MultiGenerator/Executor/TaskExecutor.hpp>
#include <MultiGenerator/Variable/Argument.hpp>
#include <MultiGenerator/Variable/DataConfig.hpp>
#include <MultiGenerator/Workflow/Task.hpp>
#include <MultiGenerator/Workflow/TaskGroup.hpp>
#include <MultiGenerator/Interface/Component.hpp>
#include <MultiGenerator/Interface/Utility.hpp>
#include <MultiGenerator/Interface/Template.hpp>

namespace MultiGenerator {
    /** Reexport some essential classes and functions */
    using Variable::DataConfig;
    using namespace Interface;
} // namespace MultiGenerator
