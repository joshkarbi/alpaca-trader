// FileWritingUtilities.hpp

#pragma once

#include "PreprocessorOptions.hpp"

#include <fstream>
#include <iostream>
#include <string>

namespace {
    std::string dashedLine() {
        return "------------------------------------------------------------------------\n";
    }
}

namespace tools
{
	
#ifndef DEBUG
    const std::string MAIN_LOG_FILE = "trader.log";
#endif
#ifdef DEBUG
    const std::string MAIN_LOG_FILE = "debug_trader.log";
#endif    

    // write logs at runtime
    void log(const std::string& message)
    {
    	// ofstream::out means create file if it doesn't exist
        std::ofstream logFile(MAIN_LOG_FILE, std::ofstream::out | std::ofstream::app);
        logFile << ::dashedLine();
        logFile << message << std::endl;
        logFile << ::dashedLine();

        std::cout << "LOGGING: " << message << std::endl;
    }
    
    // append message to file
    void appendMessage(const std::string& file, const std::string& message)
    {
    	// ofstream::out flag creates file if it doesn't exist
        // ofstream::app flag means append
        std::ofstream outFile(file, std::ofstream::out | std::ofstream::app);
        outFile << message;
    }

    // update contents of file (erasing old and replacing with new data)
    void update(const std::string& file, const std::string& message)
    {
    	// trunc flag deletes old contents
        // app flag appends message
        std::ofstream outFile(file, std::ofstream::trunc | std::ofstream::app);
        outFile << message;
    }
}
