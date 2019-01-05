//
//  Created by Joshua Karbi on 2018-08-28
//

#pragma once

#include "Stats.hpp"
#include "Strategy.hpp"

#include <string>

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
        static const std::string KEY_FILE;

        Trader();
        
        ~Trader()
        {
            // default
        }
        
        // called by main method
        inline void run()
        {
            initialize();
            runTrader();
            finishUp();
        };
        
    private:
        
        // look for code in file
        void findKeyID();
        
        // set everything up, query for current user holdings, etc.
        void initialize();
        
        // main app loop - strategy, order placement, logging
        void runTrader();
        
        // save stuff to files if anything goes wrong
        void finishUp();

        // large-scale objects
        Stats trading_stats;
        // Portfolio current_portfolio;
        Strategy current_strategy;
    };
}
