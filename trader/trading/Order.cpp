// Order.cpp

#include "Order.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/JSONUtilities.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include "../tools/PreprocessorOptions.hpp"
#include "../tools/Authentication.hpp"

#include <ctime>
#include <sstream>
#include <iostream>
#include <unistd.h>

namespace trading
{
    Order::Order(const Holding& hold)
    {
        security = new Holding(hold.getSymbol(), hold.getNumShares(), hold.getPrice(), hold.getExchange());
        
        // set time to time in human-readable string form
        std::time_t num_time = std::time(nullptr);
        timestamp = std::asctime(std::localtime(&num_time));
    }

    // Create and POST a new order
    Order::Order(const std::string& action,
     const std::string& symbol, const size_t quantity)
    {
    	std::string url = (tools::PAPER_DOMAIN+"orders");
        std::string orderID = "";
        // NOTE: Alpaca expects POST bodies in JSON format

    	std::stringstream ss;
    	ss << "{\"symbol\":\"" << symbol << "\",\"qty\":\"" <<
    		quantity << "\",\"side\":\"" << action << "\",\"type\":\"market\",\"time_in_force\":\"gtc\"}";
		std::string params = ss.str();


    	std::string auth = ("APCA-API-KEY-ID: " + tools::Authentication::key);
		std::string secret = ("APCA-API-SECRET-KEY: " + tools::Authentication::secretKey);
		std::vector<std::string> headers = {auth, secret};

		std::string apiResponse = tools::simplePost(url, "", params, headers);

		// construct Order from JSON response
		rapidjson::Document doc = tools::getDOMTree(apiResponse);
        orderID = doc["id"].GetString();

        // wait for order to execute
        usleep(500);

        // get execution price
        std::string getPriceResponse = tools::simpleGet(tools::PAPER_DOMAIN+"orders/"+orderID, "", headers);
        rapidjson::Document priceJSON = tools::getDOMTree(getPriceResponse);

		security = new Holding(doc["symbol"].GetString(), 
			std::stoi(doc["qty"].GetString()), std::stod(priceJSON["filled_avg_price"].GetString()),
			Holding::NASDAQ);

        if (action == "buy") 
        {
		    tools::log("Bought " + security->toString() + " at " + priceJSON["filled_at"].GetString());
        }
        else if (action == "sell")
        {
            tools::log("Sold " + security->toString() + priceJSON["filled_at"].GetString());
        }
    }

    std::vector<Order> Order::getAllOrders()
    {
    	std::string url = tools::PAPER_DOMAIN+"orders";
    	std::string auth = ("APCA-API-KEY-ID: " + tools::Authentication::key);
		std::string secret = ("APCA-API-SECRET-KEY: " + tools::Authentication::secretKey);
		std::vector<std::string> headers = {auth, secret};

		std::string apiResponse = tools::simpleGet(url, "", headers);

        std::vector<Order> res;
        if (apiResponse == "[]") 
        {
            // no open orders
            return res;
        }

		rapidjson::Document doc = tools::getDOMTree(apiResponse);
		auto a = doc[0].GetArray();

		// ... //

		return res;
    }

}
