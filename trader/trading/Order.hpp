//
//  Created by Joshua Karbi on 2018-08-28.
//

#pragma once

#include <string>
#include <vector>

#include "Holding.hpp"

namespace trading
{
    /**
     * Place orders, GET a list of Orders, etc.
     *
     * Orders contain a Holding object and a time the order was placed.
     */
    class Order
    {
    public:
        // place an order
        // NOTE: for now will only do market orders, good until cancelled, on NASDAQ
        // @param action - "sell" or "buy"
        Order(const std::string& action, const std::string& symbol, const size_t quantity);

        // secondary constructor
        Order(const Holding& hold);

        // GET list of orders on this account from the Alpaca API
        static std::vector<Order> getAllOrders();

        // getters
        Holding* getHolding() { return security; }
        std::string getTimestamp() { return timestamp; }
        
    private:
        Holding* security;
        std::string timestamp;
    };
}
