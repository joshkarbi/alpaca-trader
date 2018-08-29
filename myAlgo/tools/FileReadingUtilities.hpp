//
//  Created by Joshua Karbi on 2018-08-29.
//

#pragma once

#include <string>
#include <vector>

namespace tools
{
    // @return true if 'file' exists in the system
    bool fileExists(const std::string& file);
    
    // @return all the lines from the file
    std::vector<std::string> getLines(const std::string& file);
    
}
