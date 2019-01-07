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
        // main constructor
        Order(const Holding& hold);

        // place an order
        // NOTE: for now will only do market orders, good until cancelled, on NASDAQ
        // @param action - "sell" or "buy"
        Order(const std::string& action, const std::string& symbol, const size_t quantity);
        
    private:
        // One order has one "holding" which can have multiple shares
        Holding* security;
        std::string timestamp;
    };
}
