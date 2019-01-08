//
//  Created by Joshua Karbi on 2018-08-29.
//

#include "FileReadingUtilities.hpp"

#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string/erase.hpp>

namespace tools
{
    bool fileExists(const std::string& name)
    {
        std::ifstream ifile(name.c_str());
        return (bool)ifile;
    }
    
    std::vector<std::string> getLines(const std::string& name)
    {
        std::ifstream file(name);
        std::string line;
        
        std::vector<std::string> results;
        results.reserve(50);
        
        while (std::getline(file, line))
        {
            results.push_back(line);
            line.clear();
        }
        
        return results;
    }

    std::string getWholeFile(const std::string& name)
    {
        std::ifstream file(name);

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
