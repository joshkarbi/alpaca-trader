//
//  Created by Joshua Karbi on 2018-08-28.
//

#pragma once

#include <vector>

#include "Portfolio.hpp"
#include "Order.hpp"

namespace trading
{
    /**
     * Used by Trader to keep track of (and log) statistics.
     *
     * A Holding is a security with a ticker symbol,
     * exchange, number of shares, and purchase price.
     */
    class Stats
    {
    public:
        Stats() : market_diff(0), capital_gains(0)
        {
            // do nothing
        }
        ~Stats()
        {
            // do nothing
        }
        
        // Could throw if file doesn't exist
        // @return true on success
        void logStats(const Portfolio& holdings) const;
        
    private:
        // updates to portfolios "market value"
        int market_diff;
        
        // if sell orders were placed, keep track of earnings
        int capital_gains;
        
        // all orders placed today
        std::vector<Order> orders;
    };
}
