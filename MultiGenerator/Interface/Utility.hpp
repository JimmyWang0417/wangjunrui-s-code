/**
 * @file MultiGenerator/Interface/Utility.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief Some helper functions.
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>

#include <MultiGenerator/Variable/Argument.hpp>

namespace MultiGenerator::Interface {
    /**
     * @brief Create an entry for DataConfig.
     * 
     * @tparam Value the type of the value
     * @param key the key in the entry
     * @param value the value in the entry
     * @return std::pair<std::string, std::string> the entry
     */
    template <typename Value>
    inline std::pair<std::string, std::string> entry(const std::string &key, const Value &value) {
        return { key, std::to_string(value) };
    }

    /**
     * @brief Create a NormalArgument instance.
     * 
     * @param id the ID of this testcase
     * @param config the config of this testcase
     * @return std::shared_ptr<Variable::Argument> the instance
     */
    inline std::shared_ptr<Variable::Argument> testcase(int id,
        const std::unordered_map<std::string, std::string> &config) {
        return std::make_shared<Variable::NormalArgument>(id, config);
    }

    /**
     * @brief Create a SubtaskArgument instance
     * 
     * @param subtaskId the subtask ID of this testcase
     * @param id the ID of this testcase
     * @param config the config of this testcase
     * @return std::shared_ptr<Variable::Argument> the instance
     */
    inline std::shared_ptr<Variable::Argument> testcase(int subtaskId, int id,
        const std::unordered_map<std::string, std::string> &config) {
        return std::make_shared<Variable::SubtaskArgument>(subtaskId, id, config);
    }
} // namespace MultiGenerator::Interface
