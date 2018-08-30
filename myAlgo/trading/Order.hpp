//
//  Created by Joshua Karbi on 2018-08-28.
//

#pragma once

#include <string>

#include "Holding.hpp"

namespace trading
{
    /**
     * Used by Stats to keep track of orders placed.
     *
     * Orders contain a Holding object and a time the order was placed.
     */
    class Order
    {
    public:
        Order()
        {
            // do nothing
        }
        ~Order() = default;
        
        // main constructor
        Order(const Holding& hold);
        
    private:
        // One order has one "holding" which can have multiple shares
        Holding security;
        std::string time;
    };
}
