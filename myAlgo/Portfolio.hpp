//
//  Created by Joshua Karbi on 2018-08-28.
//

#pragma once

#include <stdint.h>
#include <stddef.h>

#include <unordered_set>

#include "Holding.hpp"

namespace trading
{
    /**
     * Used by Trader to keep track of holdings and cash left.
     */
    class Portfolio
    {
    public:
        Portfolio()
        {
            // do nothing
        };
        ~Portfolio()
        {
            // do nothing
        };
        
        // query Tradier API to retrieve current User data
        // return true on success
        bool update();
        
        // getters
        uint32_t getCash() const { return cash; };
        size_t getNumHoldings() const { return holdings.size(); };
        
        // can use range-based for to write to files at end of each day or trade
        std::unordered_set<Holding> getHoldings() const { return holdings; };
        
    private:
        // money in account
        uint32_t cash;
        
        // securities currently held
        std::unordered_set<Holding> holdings;
    };
}
