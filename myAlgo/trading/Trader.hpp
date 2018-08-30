//
//  Created by Joshua Karbi on 2018-08-28
//

#pragma once

#include <string>

#include "Stats.hpp"
#include "Portfolio.hpp"

namespace trading
{
    const std::string AUTH_CODE_FILE_PATH = "/tmp/auth_code.txt";
    
    /**
     * Main application object.
     *
     * Manage holdings, orders, and other application objects.
     */
    class Trader
    {
    public:
        Trader();
        
        ~Trader()
        {
            // do nothing
        };
        
        // called by main method
        void run();
        
    private:
        
        // look for code in file
        void findAuthCode();
        
        // set everything up, query for current user holdings, etc.
        void initialize();
        
        // main app loop - strategy, order placement, logging
        void runTrader();
        
        // save stuff to files if anything goes wrong
        void finishUp();
        
        
        // private variables
        std::string auth_code;
        std::string token;
        Stats trading_stats;
        Portfolio current_portfolio;
    };
}
