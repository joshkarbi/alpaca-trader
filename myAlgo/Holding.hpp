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
        ~Holding() { };
        
        // TODO: put some getters and setters
        
    private:
        
        // ie. "APPL"
        std::string symbol;
        
        // "NYSE", "NASDAQ", "TSX", etc.
        std::string exchange;
        
        // in USD
        double purchase_price;
        
        int num_shares;
    };
}
