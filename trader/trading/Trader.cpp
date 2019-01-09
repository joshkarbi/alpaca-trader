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
#include "../tools/MarketData.hpp"

#include "Strategy.hpp"

#include <fstream>
#include <iostream>
#include <ctime>
#include <assert.h>
#include <cmath>

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

        // do on init (from config file)
        watchlist = Strategy::getWatchlist();
    }

    void Trader::runTrader()
    {
        // for each holding we own -> check if we should sell it
        for (const Holding& stock : currentHoldings)
        {
            if (Strategy::shouldSell(stock.getSymbol()))
            {
                // place buy Order (logging and console output taken care of)
                Order* buyDecision = new Order("buy", stock.getSymbol(), getSharesToBuy(stock.getSymbol()));

                // update the holdings, cash left available
                currentHoldings = tools::AccountData::getAccountPositions();
                tools::AccountData::updateCashBalance();

                delete buyDecision;
            }
        }

        // for each stock we are tracking, see if we should buy it
        for (const Stock& stock : watchlist)
        {
            if (Strategy::shouldBuy(stock.getSymbol()))
            {
                // place sell order
                Order* sellDecision = new Order("sell", stock.getSymbol(), getSharesToSell(stock.getSymbol()));
                
                // update holdings and cash left available
                currentHoldings = tools::AccountData::getAccountPositions();
                tools::AccountData::updateCashBalance();

                delete sellDecision;
            }
        }
    }

    size_t Trader::getSharesToBuy(const std::string& symbol)
    {
        size_t stocksWeCanOwn = Strategy::getStocksToOwn();
        double cashAvailable = tools::AccountData::getCashBalance();
        size_t numStocksOwned = currentHoldings.size();
        double reserveCash = Strategy::getMinCash();

        double cashToSpend = (cashAvailable - reserveCash)/(stocksWeCanOwn - numStocksOwned);

        double shares = cashToSpend/(tools::MarketData::getPrices({symbol})[0]);

        return static_cast<size_t>(floor(shares));
    }

    // for now if we want to sell, sell all shares of 'symbol'
    size_t Trader::getSharesToSell(const std::string& symbol)
    {
        for (const Holding& hold : currentHoldings)
        {
            if (hold.getSymbol() == symbol)
            {
                return hold.getNumShares();
            }
        }

        return 0;
    }

    void Trader::finishUp()
    {
        // write the trading day's stats to a file.
        // ie. trading_stats.logStats(file_path);
    }
}
