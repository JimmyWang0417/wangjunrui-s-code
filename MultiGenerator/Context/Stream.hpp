/**
 * @file MultiGenerator/Context/Stream.hpp
 * @author Justin Chen (ctj12461@163.com)
 * @brief This file contains some wrappers of IO streams in C++ standard library.
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <exception>

namespace MultiGenerator::Context {
    class FileOpenFailedException : std::exception {
    public:
        FileOpenFailedException(const std::string &fileName) :
            msg("FileOpenFailedException: Failed to open file: " + fileName) {}
        
        const char *what() const noexcept override {
            return msg.c_str();
        }
    private:
        std::string msg;
    };
    
    /**
     * @brief An interface which declares a standard behavior to get an input stream.
     * 
     */
    class InputStream {
    public:
        InputStream() {}

        virtual ~InputStream() {}
        
        virtual std::istream &getStream() = 0;
    };

    class StandardInputStream : public InputStream {
    public:
        StandardInputStream() :
            InputStream() {}

        ~StandardInputStream() {}
        
        virtual std::istream &getStream() override {
            return std::cin;
        }
    };

    class FileInputStream : public InputStream {
    public:
        FileInputStream(const std::string &fileName) :
            fileName(fileName),
            ifs() {}

        ~FileInputStream() {}

        virtual std::istream &getStream() override {
            if (!ifs.is_open())
                ifs.open(fileName);

            if (ifs.fail())
                throw FileOpenFailedException(fileName);
            
            return ifs;
        }
    private:
        std::string fileName;
        std::ifstream ifs;
    };

    /**
     * @brief An interface which declares a standard behavior to get an output stream.
     * 
     */
    class OutputStream {
    public:
        OutputStream() {}

        virtual ~OutputStream() {}

        virtual std::ostream &getStream() = 0;
    };

    class StandardOutputStream : public OutputStream {
    public:
        StandardOutputStream() :
            OutputStream() {}

        ~StandardOutputStream() {}
        
        virtual std::ostream &getStream() override {
            return std::cout;
        }
    };

    class FileOutputStream : public OutputStream {
    public:
        FileOutputStream(const std::string &fileName) :
            fileName(fileName),
            ofs() {}

        ~FileOutputStream() {}

        virtual std::ostream &getStream() override {
            if (!ofs.is_open())
                ofs.open(fileName);

            if (ofs.fail())
                throw FileOpenFailedException(fileName);
            
            return ofs;
        }
    private:
        std::string fileName;
        std::ofstream ofs;
    };
} // namespace MultiGenerator::Context