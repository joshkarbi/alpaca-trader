// Trader.cpp
// Main algo logic

#include "Trader.hpp"

#include "../tools/FileReadingUtilities.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/PreprocessorOptions.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/JSONUtilities.hpp"

#include "Strategy.hpp"

#include <fstream>
#include <iostream>
#include <ctime>
#include <assert.h>

namespace trading
{   
    void Trader::initialize()
    {
        // MUST BE DONE FIRST
        tools::Authentication::setup();

        // set currentPortfolio to AccountData::getPositions()
        
        // returns true on success
        if ( ! Strategy::setup()) {
            throw std::runtime_error("ERROR: Failed to initialize Strategy in Trader::initialize().");
        }
    }

    void Trader::runTrader()
    {
        // get access token
        // query prices
        // change positions
        
        // update stats by appending to Orders vector
        // update portfolio (cash left and holdings)
    }

    void Trader::finishUp()
    {
        // write the trading day's stats to a file.
        // ie. trading_stats.logStats(file_path);
    }
}
