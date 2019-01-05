//
//  Created by Joshua Karbi on 2018-08-29.
//

#pragma once

#include <string>

namespace tools
{
    const std::string MAIN_LOG_FILE = "trader.log";
    
    // write logs at runtime
    void log(const std::string& message);
    
    // append message to file
    void appendMessage(const std::string& file, const std::string& message);

    // update contents of file (erasing old and replacing with new data)
    void update(const std::string& file, const std::string& message);
}
