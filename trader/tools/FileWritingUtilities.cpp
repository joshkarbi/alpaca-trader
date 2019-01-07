// FileWritingUtilities.cpp

#include "FileWritingUtilities.hpp"
#include "PreprocessorOptions.hpp"

#include <fstream>
#include <iostream>

namespace tools
{
    void log(const std::string& message)
    {
        // ofstream::out means create file if it doesn't exist
#ifndef DEBUG
        std::ofstream logFile(MAIN_LOG_FILE, std::ofstream::out);
#endif
#ifdef DEBUG
        std::ofstream logFile("debug_"+MAIN_LOG_FILE, std::ofstream::out);
#endif
        logFile << "---------------------------------------------\n";
        logFile << message << std::endl;
        logFile << "---------------------------------------------\n";

        std::cout << "LOGGING: " << message << std::endl;
    }
    
    void appendMessage(const std::string& file, const std::string& message)
    {
        // ofstream::out flag creates file if it doesn't exist
        // ofstream::app flag means append
        std::ofstream outFile(file, std::ofstream::out | std::ofstream::app);
        outFile << message;
    }

    void update(const std::string& file, const std::string& message)
    {
        // trunc flag deletes old contents
        // app flag appends message
        std::ofstream outFile(file, std::ofstream::trunc | std::ofstream::app);
        outFile << message;
    }
}
