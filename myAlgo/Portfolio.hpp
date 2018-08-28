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

#include <vector>

#include "Holding.hpp"

namespace trading
{
    class Portfolio
    {
    public:
        Portfolio();
        ~Portfolio() {};
        
        // query Tradier API to retrieve current User data
        // return true on success
        bool update();
        
        // GETTERS
        std::vector<Holding> getHoldings() const { return holdings; };
        uint32_t getCash() const { return cash; };
        size_t getNumHoldings() const { return holdings.size(); };
    private:
        
        // money in account
        uint32_t cash;
        
        // securities currently held
        std::vector<Holding> holdings;
    };
}
