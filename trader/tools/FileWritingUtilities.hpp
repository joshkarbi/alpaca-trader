// FileWritingUtilities.hpp

#pragma once

#include "PreprocessorOptions.hpp"

#include <string>

namespace tools
{
	
#ifndef DEBUG
    const std::string MAIN_LOG_FILE = "trader.log";
#endif
#ifdef DEBUG
    const std::string MAIN_LOG_FILE = "debug_trader.log";
#endif    

    // write logs at runtime
    void log(const std::string& message);
    
    // append message to file
    void appendMessage(const std::string& file, const std::string& message);

    // update contents of file (erasing old and replacing with new data)
    void update(const std::string& file, const std::string& message);
}
