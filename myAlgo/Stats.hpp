//
//  Stats.hpp
//
//  Created by Joshua Karbi on 2018-08-28.
//

#pragma once

#include "Portfolio.hpp"

namespace trading
{
    // keeps track of the day's statistics
    class Stats
    {
    public:
        Stats() : todays_earnings(0), orders_placed(0)
        {
            // do nothing
        }
        ~Stats()
        {
            // do nothing
        }
        
        // Could throw if file doesn't exist
        // @return true on success
        bool logStats(const std::string& file_path, const Portfolio& holdings) const;
        
    private:
        // could be zero
        int todays_earnings;
        size_t orders_placed;
        
    };
}
