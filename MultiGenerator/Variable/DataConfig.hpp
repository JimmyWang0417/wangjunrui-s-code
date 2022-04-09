/**
 * @file MultiGenerator/Variable/DataConfig.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief This file contains DataConfig which provides the ability to save and 
 * access the arguments (n = ?, m = ?) for each test case easily.
 * @version 0.1
 * @date 2022-03-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <unordered_map>
#include <optional>

namespace MultiGenerator::Variable {
    /**
     * @brief A simple object to store some configure for a test case.
     *
     */
    class DataConfig {
    public:
        DataConfig() : config() {}

        DataConfig(const std::unordered_map<std::string, std::string> &config) :
            config(config) {}

        ~DataConfig() {};

        /**
         * @brief Insert a string pair (key, value), return false if key already exists.
         *
         * @param key the index
         * @param value the value binding to key
         * @return false key already exists, true otherwise
         */
        bool insert(const std::string &key, const std::string &value) {
            if (config.find(key) != config.end())
                return false;

            config.insert({ key, value });
            return true;
        }

        /**
         * @brief Change the value binding to key to newValue, insert one if key doesn't exist.
         *
         * @param key the index
         * @param newValue the new value
         */
        void change(const std::string &key, const std::string &newValue) {
            config[key] = newValue;
        }

        /**
         * @brief Remove the key and the value binding to it.
         *
         * @param key
         * @return false if key doesn't exist, true otherwise
         */
        bool erase(const std::string &key) {
            if (auto it = config.find(key); it == config.end()) {
                return false;
            } else {
                config.erase(it);
                return true;
            }
        }

        /**
         * @brief check whether key exists
         *
         * @param key
         * @return true or false
         */
        bool contain(const std::string &key) const {
            return config.find(key) != config.end();
        }

        /**
         * @brief Get the wrapper of the value
         *
         * @param key the index
         * @return the std::optional wrapper of the value or std::nullopt if key doesn' exists
         */
        std::optional<std::string> get(const std::string &key) const {
            if (auto it = config.find(key); it == config.end())
                return std::nullopt;
            else
                return it->second;
        }

        /**
         * @brief Get the value or the default value if key doesn't exist.
         *
         * @param key the index
         * @param defaultValue the default value
         * @return std::string or the default value
         */
        std::string getOr(const std::string &key, const std::string defaultValue) const {
            if (auto it = config.find(key); it == config.end())
                return defaultValue;
            else
                return it->second;
        }

        static DataConfig create(const std::unordered_map<std::string, std::string> &config) {
            return DataConfig(config);
        }
    private:
        std::unordered_map<std::string, std::string> config;
    };
} // namespace MultiGenerator::Variable