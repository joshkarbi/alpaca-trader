//
//  Created by Joshua Karbi on 2018-08-29.
//

#pragma once

#include <string>

namespace tools
{
    const std::string MAIN_LOG_FILE = "/tmp/trader.log";
    
    // write logs at runtime
    void log(const std::string& message);
}
