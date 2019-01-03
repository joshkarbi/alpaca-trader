//
//  Created by Joshua Karbi on 2018-08-29.
//

#include "FileWritingUtilities.hpp"

#include <fstream>

namespace tools
{
    void log(const std::string& message)
    {
        // ofstream::out means create file if it doesn't exist
        std::ofstream logFile(MAIN_LOG_FILE, std::ofstream::out);
        logFile << "---------------------------------------------\n";
        logFile << message << std::endl;
        logFile << "---------------------------------------------\n";
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
