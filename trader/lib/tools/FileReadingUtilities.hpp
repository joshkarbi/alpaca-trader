// FileReadingUtilities.cpp

#pragma once

#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string/erase.hpp>
#include <string>
#include <vector>

namespace tools
{
    // @return true if 'fileName' exists in the system
    bool fileExists(const std::string& fileName)
    {
    	std::ifstream ifile(fileName.c_str());
        return (bool)ifile;
    }
    
    // @return all the lines from the file
    // Note: skips lines starting with '#', and empty lines
    std::vector<std::string> getLines(const std::string& fileName)
    {
    	std::ifstream file(fileName);
        std::string line;
        
        std::vector<std::string> results;
        results.reserve(50);
        
        while (std::getline(file, line))
        {
            // always skip comments and empty lines
            if (line.empty() || line[0] == '#') { continue; }
            
            results.push_back(line);
            line.clear();
        }
        
        return results;
    }

    // @return whole file as one string (ie. for JSON config files)
    // Note: lines will be stripped of newline and whitespace character
    std::string getWholeFile(const std::string& fileName)
    {
    	std::ifstream file(fileName);

        std::string line;
        std::string fileAsString;
        
        while (std::getline(file, line))
        {
            if (line[0] == '#' || line.empty()) { continue; }

            boost::algorithm::erase_all(line, " ");
            boost::algorithm::erase_all(line, "\n");
            fileAsString += line;
            line.clear();
        }
        
        return fileAsString;
    }
}
