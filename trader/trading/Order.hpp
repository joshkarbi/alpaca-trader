// Order.hpp

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
        ~Order()
        {
            if (security != nullptr)
            {
                delete security;
            }
        }

        // place an order (buy or sell)
        // NOTE: for now will only do market orders for US securities, good until cancelled
        // @param action - "sell" or "buy"
        // @param symbol - ticker symbol (i.e. "AAPL")
        // @param quantity - number of shares 
        Order(const std::string& action, const std::string& symbol, size_t quantity);

        // secondary constructor
        Order(const Holding& hold);

        // GET list of orders on this account from the Alpaca API
        static std::vector<Order> getAllOrders();

        // cancel an order
        static void cancelOrder(const std::string& orderID);
        
        // getters
        Holding* getHolding() { return security; }
        std::string getTimestamp() { return timestamp; }
        
    private:
        Holding* security;
        std::string timestamp;
    };
}
