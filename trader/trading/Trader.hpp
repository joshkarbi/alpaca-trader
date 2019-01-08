// Trader.hpp

#pragma once

#include "Stats.hpp"
#include "Strategy.hpp"
#include "Holding.hpp"

#include <string>
#include <vector>

namespace trading
{   
    /**
     * Main application object.
     *
     * Manage holdings, orders, and other application objects.
     */
    class Trader
    {
    public:
        // called by main method
        inline void run()
        {
            initialize();
            runTrader();
            finishUp();
        };
        
    private:
        // set everything up, query for current user holdings, etc.
        void initialize();
        
        // main app loop - strategy, order placement, logging
        void runTrader();
        
        // save stuff to files if anything goes wrong
        void finishUp();

        // big logic objects
        std::vector<Holding> currentHoldings;
        Stats tradingStats;
    };
}
