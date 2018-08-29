//
//  Created by Joshua Karbi on 2018-08-29.
//

#include "Logger.hpp"
#include "FileReadingUtilities.hpp"

#include <fstream>

namespace tools
{
    void log(const std::string& message)
    {
        std::ofstream logFile(MAIN_LOG_FILE);
        logFile << "---------------------------------------------\n";
        logFile << message << std::endl;
        logFile << "---------------------------------------------\n";
    }
}
