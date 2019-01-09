// FileWritingUtilities.cpp

#include "FileWritingUtilities.hpp"
#include "PreprocessorOptions.hpp"

#include <fstream>
#include <iostream>

namespace {
    std::string dashedLine() {
        return "------------------------------------------------------------------------\n";
    }
}
namespace tools
{
    void log(const std::string& message)
    {
        // ofstream::out means create file if it doesn't exist
        std::ofstream logFile(MAIN_LOG_FILE, std::ofstream::out | std::ofstream::app);
        logFile << ::dashedLine();
        logFile << message << std::endl;
        logFile << ::dashedLine();

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
