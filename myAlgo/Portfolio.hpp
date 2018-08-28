//
//  Portfolio.hpp
//  myAlgo
//
//  Created by Joshua Karbi on 2018-08-28.
//  Copyright © 2018 Joshua Karbi. All rights reserved.
//

#pragma once

#include <stdint.h>
#include <vector>

namespace trading
{
    // forward declaration
    class Holding;
    
    class Portfolio
    {
    public:
        Portfolio();
        ~Portfolio() = default;
        
        // query Tradier API to retrieve current User data
        // return true on success
        bool initialize();
        
    private:
        uint32_t cash;
        uint32_t numHoldings;
        std::vector<Holding> holdings;
    };
}
