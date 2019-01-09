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
#include <unistd.h>

namespace
{
    void print(const std::string& message)
    {
        std::cout << message << std::endl;
    }
}
namespace trading
{   
    void Trader::initialize()
    {
        // MUST BE DONE FIRST
        tools::Authentication::setup();
        ::print("AUTHENTICATION SETUP COMPLETE");

        tools::AccountData::updateCashBalance();
        ::print("UPDATED CASH BALANCE");
        
        if (! tools::AccountData::accountIsActive())
        {
            std::string error = "ERROR: Account is not in \"ACTIVE\" state.";
            std::cout << error << std::endl;
            throw std::runtime_error(error);
        }
        ::print("ACCOUNT IS ACTIVE CHECK COMPLETE");

        // returns true on success
        if ( ! Strategy::setup())
        {
            std::string error = "ERROR: Failed to setup Strategy in Trader::initialize().";
            std::cout << error << std::endl;
            throw std::runtime_error(error);
        }
        ::print("STRATEGY SETUP COMPLETE");

        currentHoldings = tools::AccountData::getAccountPositions();
        ::print("CURRENT HOLDINGS SAVED");

        // do on init (from config file)
        watchlist = Strategy::getWatchlist();
        ::print("WATCHLIST SAVED");
    }

    void Trader::runTrader()
    {
        // for each holding we own -> check if we should sell it
        try 
        {

            for (const Holding& stock : currentHoldings)
            {
                if (Strategy::shouldSell(stock.getSymbol()))
                {
                    // place buy Order (logging and console output taken care of)
                    Order* sellDecision = new Order("sell", stock.getSymbol(), getSharesToSell(stock.getSymbol()));

                    // update the holdings, cash left available
                    currentHoldings = tools::AccountData::getAccountPositions();
                    tools::AccountData::updateCashBalance();

                    delete sellDecision;
                }
            }

            // for each stock we are tracking, see if we should buy it
            for (const Stock& stock : watchlist)
            {
                if (Strategy::shouldBuy(stock.getSymbol()))
                {
                    // place buy order
                    Order* buyDecision = new Order("buy", stock.getSymbol(), getSharesToBuy(stock.getSymbol()));
                
                    // update holdings and cash left available
                    currentHoldings = tools::AccountData::getAccountPositions();
                    tools::AccountData::updateCashBalance();

                    delete buyDecision;
                }
            }
        }
        catch (const std::runtime_error& e)
        {
            // queries could throw
            // ie. IEX or Alpaca API is offline, or market is closed and JSON is malformed
            tools::log("ERROR in Trader::runTrader()");

            // sleep a bit then continue the loop
            usleep(1000);
        }
    }

    // split cash evenly across specified stocks to own (from config)
    size_t Trader::getSharesToBuy(const std::string& symbol)
    {
        size_t stocksWeCanOwn = Strategy::getStocksToOwn();
        double cashAvailable = tools::AccountData::getCashBalance();
        size_t numStocksOwned = currentHoldings.size();
        double reserveCash = Strategy::getMinCash();

        double cashToSpend = (cashAvailable - reserveCash)/(stocksWeCanOwn - numStocksOwned);

        double shares = cashToSpend/(tools::MarketData::getPrices({symbol})[0]);

        std::cout << "Stocks we can own: " << stocksWeCanOwn << std::endl;
        std::cout << "Cash available: " << cashAvailable << std::endl;
        std::cout << "Num stocks owned: " << numStocksOwned << std::endl;
        std::cout << "Reserve cash level: " << reserveCash << std::endl;
        std::cout << "Cash to spend on trade: " << cashToSpend << std::endl;
        std::cout << "SHARES TO BUY: " << shares << std::endl;

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
