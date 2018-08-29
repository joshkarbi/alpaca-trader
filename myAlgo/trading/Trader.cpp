//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Trader.hpp"

// Dependency: cpr networking library
// TODO: use angle include
#include "../../cpr/cpr.h"

namespace trading
{
    /**
     * Read from config file.
     */
    void Trader::run()
    {
        initialize();
        runTrader();
        finishUp();
    }
    
    void Trader::initialize()
    {
        // TODO: query for current user holdings
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
