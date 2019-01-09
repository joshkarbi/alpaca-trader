// Trader.cpp
// Main algo logic

#include "Trader.hpp"

#include "../tools/FileReadingUtilities.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/PreprocessorOptions.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/JSONUtilities.hpp"
#include "../tools/AccountData.hpp"

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

        if (! tools::AccountData::accountIsActive())
        {
            throw std::runtime_error("ERROR: Account is not in \"ACTIVE\" state.");
        }

        currentHoldings = tools::AccountData::getAccountPositions();

        // returns true on success
        if ( ! Strategy::setup())
        {
            throw std::runtime_error("ERROR: Failed to initialize Strategy in Trader::initialize().");
        }
    }

    void Trader::runTrader()
    {
        for (const Holding& stock : currentHoldings)
        {
            if (Strategy::shouldSell(stock.getSymbol()))
            {
                // place buy Order
            }
        }

        std::vector<Stock>& watchlist = Strategy::getWatchlist();
        for (const Stock& stock : watchlist)
        {
            if (Strategy::shouldBuy(stock.getSymbol()))
            {
                // place sell order
            }
        }
    }

    void Trader::finishUp()
    {
        // write the trading day's stats to a file.
        // ie. trading_stats.logStats(file_path);
    }
}
