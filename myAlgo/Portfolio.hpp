//
//  Portfolio.hpp
//  myAlgo
//
//  Created by Joshua Karbi on 2018-08-28.
//  Copyright © 2018 Joshua Karbi. All rights reserved.
//

#pragma once

#include <stdint.h>
#include <stddef.h>

#include <unordered_set>

#include "Holding.hpp"

namespace trading
{
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
        
        // GETTERS
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
