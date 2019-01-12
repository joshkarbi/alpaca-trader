//
// An algorithmic trading application built to work with the
// Alpaca Markets brokerage API.
// 
// Main method -> no logic, just startup and log any errors
// 

#include "trading/Trader.hpp"
#include "tools/FileWritingUtilities.hpp"
#include "tools/PreprocessorOptions.hpp"
#include "trading/Order.hpp"
#include "tools/Authentication.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char **argv) 
{
    if (argc != -1)
    {
        // allow for manual placement of orders through command line
        tools::Authentication::setup();

        std::string action, orderID, symbol;
        size_t quantity;
        std::cout << " buy, sell, or cancel: ";
        std::cin >> action;
        if (action == "cancel")
        {
            std::cout << "Order ID: ";
            std::cin >> orderID;
            trading::Order::cancelOrder(orderID);
            return 0;
        }

        std::cout << "symbol: ";
        std::cin >> symbol;
        std::cout << "quantity: ";
        std::cin >> quantity;
        trading::Order* placeOrder = new trading::Order(action, symbol, quantity);
        delete placeOrder;
    }
    try 
    {
    	trading::Trader app;
    	app.run();
    } catch (const std::exception& e)
    {
    	// log any errors thrown up to main
    	tools::log(e.what());
    	std::cout << "Logging: " << e.what() << std::endl;
    }

    return 0;
}
