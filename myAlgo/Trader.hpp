/**
 *
 *
 *
 *
 **/

#pragma once

#include <string>

namespace trading
{
    class Portfolio;
    class Stats;
    
    class Trader
    {
    public:
        Trader()
        {
            // do nothing;
        };
        ~Trader() {};
        
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
        std::string authCode;
        std::string token;
        // other objects
        // Stats?
        // Portfolio object?
    };
}
