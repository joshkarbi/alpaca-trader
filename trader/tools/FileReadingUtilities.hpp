// FileReadingUtilities.cpp

#pragma once

#include <string>
#include <vector>

namespace tools
{
    // @return true if file exists
    bool fileExists(const std::string& file);
    
    // @return all the lines from the file
    std::vector<std::string> getLines(const std::string& file);

    // @return whole file as one string (ie. for JSON config files)
    // Note: lines will be stripped of newline and whitespace characters
    std::string getWholeFile(const std::string& file);
}
