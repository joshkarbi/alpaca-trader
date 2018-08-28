//
//  Holding.cpp
//  myAlgo
//
//  Created by Joshua Karbi on 2018-08-28.
//  Copyright © 2018 Joshua Karbi. All rights reserved.
//

#include "Holding.hpp"

namespace trading
{

    // do not take into account price or number of shares
    bool Holding::operator==(const Holding& other) const
    {
        if (symbol == other.getSymbol() && exchange == other.getExchange())
        {
            return true;
        }
        return false;
    }

}
