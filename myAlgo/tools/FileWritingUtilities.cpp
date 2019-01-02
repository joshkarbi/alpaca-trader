//
//  Created by Joshua Karbi on 2018-08-29.
//

#include "Logger.hpp"

#include <fstream>

namespace tools
{
    void log(const std::string& message)
    {
        std::ofstream logFile(MAIN_LOG_FILE);
        logFile << "---------------------------------------------\n";
        logFile << message << std::endl;
        logFile << "---------------------------------------------\n";

        // closing the file is done implicitly by ofstream destructor
    }
    
    void appendMessage(const std::string& file, const std::string& message)
    {
        std::ofstream outFile(file);
        outFile << message;
    }
}
