//
//  Holding.hpp
//  myAlgo
//
//  Created by Joshua Karbi on 2018-08-28.
//  Copyright © 2018 Joshua Karbi. All rights reserved.
//

#pragma once
#include <stdint.h>
#include <string>
namespace trading
{
    // one holding has only a few data points
    class Holding
    {
    public:
        Holding();
        ~Holding() = default;
        
        // TODO: put some getters and setters
        
    private:
        uint32_t purchase_price;
        uint32_t current_price;
        std::string symbol;
        // "NYSE", "NASDAQ", "TSX", etc.
        std::string exchange;
    };
}
