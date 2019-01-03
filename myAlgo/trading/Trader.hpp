//
//  Created by Joshua Karbi on 2018-08-28
//

#pragma once

#include <string>

#include "Stats.hpp"
#include "Strategy.hpp"

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
        void findClientID();
        
        // set everything up, query for current user holdings, etc.
        void initialize();
        
        // main app loop - strategy, order placement, logging
        void runTrader();
        
        // save stuff to files if anything goes wrong
        void finishUp();
        
        
        // private variables
        std::string client_id;
        std::string token;
        std::string api_url;
        std::string user_pass;

        // large-scale objects
        Stats trading_stats;
        // Portfolio current_portfolio;
        Strategy current_strategy;
    };
}
