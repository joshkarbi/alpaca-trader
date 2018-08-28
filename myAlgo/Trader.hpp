/**
 *
 *
 *
 *
 **/

#pragma once

#include <string>

#include "Stats.hpp"
#include "Portfolio.hpp"

namespace trading
{
    class Trader
    {
    public:
        Trader()
        {
            // do nothing
        };
        
        ~Trader()
        {
            // do nothing
        };
        
        void run()
        {
            initialize();
            runTrader();
            finishUp();
        }
        
        void initialize();
        void runTrader();
        void finishUp();
        
    private:
        std::string auth_code;
        std::string token;
        Stats trading_stats;
        Portfolio current_portfolio;
    };
}
