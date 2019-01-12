// Order.hpp

#pragma once

#include "Order.hpp"
#include "Holding.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/JSONUtilities.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include "../tools/PreprocessorOptions.hpp"
#include "../tools/Authentication.hpp"

#include <ctime>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

namespace
{
    void debugMessage(const std::string& message)
    {
#ifdef DEBUG 
        std::cout << message << std::endl;
#endif
    }
}


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
		// @throws on failure
	 	Order(const std::string& action, const std::string& symbol, size_t quantity)
	 	{
	 		std::string url = (tools::PAPER_DOMAIN+"orders");
	 		std::string orderID = "";
        	// NOTE: Alpaca expects POST bodies in JSON format

	 		std::string apiResponse;
	 		std::vector<std::string> headers;
	 		do {
	 			std::stringstream ss;
	 			ss << "{\"symbol\":\"" << symbol << "\",\"qty\":\"" <<
	 			quantity << "\",\"side\":\"" << action << "\",\"type\":\"market\",\"time_in_force\":\"gtc\"}";
	 			std::string params = ss.str();


	 			std::string auth = ("APCA-API-KEY-ID: " + tools::Authentication::key);
	 			std::string secret = ("APCA-API-SECRET-KEY: " + tools::Authentication::secretKey);
	 			headers = {auth, secret};

	 			apiResponse = tools::simplePost(url, "", params, headers);
	 			::debugMessage(apiResponse);

            	// try to buy one less share if this failed
	 			quantity--;
	 		} while (apiResponse.find("insufficient buying power") != std::string::npos);

			// construct Order from JSON response
	 		rapidjson::Document doc = tools::getDOMTree(apiResponse);
	 		orderID = doc["id"].GetString();

        	// wait for order to execute
	 		usleep(1000);

        	// get execution price
	 		std::string getPriceResponse = tools::simpleGet(tools::PAPER_DOMAIN+"orders/"+orderID, "", headers);
	 		::debugMessage("Trying to find execution price.");
	 		::debugMessage(getPriceResponse);

	 		rapidjson::Document priceJSON = tools::getDOMTree(getPriceResponse);

	 		double filledPrice = 0;
	 		if ( ! priceJSON["filled_avg_price"].IsNull()) 
	 		{
            	// will be null if order still hasnt gone through
	 			filledPrice = std::stod(priceJSON["filled_avg_price"].GetString());
	 		}

        	// check for failure
	 		if ( ! priceJSON["failed_at"].IsNull())
	 		{
	 			throw std::runtime_error("Failed to place " + action + " order of " + symbol + "!");
	 		}

	 		security = new Holding(doc["symbol"].GetString(), 
	 			std::stoi(doc["qty"].GetString()), filledPrice,
	 			"NASDAQ");

	 		std::string priceString = (filledPrice==0) ? "UNKNOWN PRICE" : std::to_string(filledPrice);
	 		if (action == "buy") 
	 		{
	 			tools::log("Bought " + security->toString() + " at " + priceString);
	 		}
	 		else if (action == "sell")
	 		{
	 			tools::log("Sold " + security->toString() + priceString);
	 		}
	 	}

		// secondary constructor
	 	Order(const Holding& hold)
	 	{
	 		security = new Holding(hold.getSymbol(), hold.getNumShares(), hold.getPrice(), hold.getExchange());
        
        	// set time to time in human-readable string form
        	std::time_t num_time = std::time(nullptr);
        	timestamp = std::asctime(std::localtime(&num_time));
	 	}

		// GET list of orders on this account from the Alpaca API
	 	static std::vector<Order> getAllOrders()
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

		// cancel an order
	 	static void cancelOrder(const std::string& orderID)
	 	{
	 		std::string url = tools::PAPER_DOMAIN+"orders/"+orderID;
	 		std::string auth = ("APCA-API-KEY-ID: " + tools::Authentication::key);
	 		std::string secret = ("APCA-API-SECRET-KEY: " + tools::Authentication::secretKey);
	 		std::vector<std::string> headers = {auth, secret};

	 		std::string apiResponse = tools::simpleDelete(url, headers);

	 		std::cout << "Cancelled order: " << orderID << std::endl;
	 	}

		// getters
	 	Holding* getHolding() { return security; }
	 	std::string getTimestamp() { return timestamp; }

	 private:
	 	Holding* security;
	 	std::string timestamp;
	 };
	}
