//
//  Created by Joshua Karbi on 2018-08-29.
//

#include "FileReadingUtilities.hpp"

#include <fstream>
#include <string>

namespace tools
{
    bool fileExists(const std::string& name)
    {
        if (FILE *file = fopen(name.c_str(), "r"))
        {
            fclose(file);
            return true;
        }
        return false;
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
}
