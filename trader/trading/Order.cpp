//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Order.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/JSONUtilities.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include "../tools/PreprocessorOptions.hpp"
#include "../tools/Authentication.hpp"

#include <ctime>
#include <sstream>
#include <iostream>

namespace trading
{
    Order::Order(const Holding& hold)
    {
        *security = hold;
        
        // set time to time in human-readable string form
        std::time_t num_time = std::time(nullptr);
        timestamp = std::asctime(std::localtime(&num_time));
    }

    // Create and POST a new order
    Order::Order(const std::string& action,
     const std::string& symbol, const size_t quantity)
    {
    	std::string url = (tools::PAPER_DOMAIN+"orders");

    	std::stringstream ss;
    	ss << "symbol=" << symbol << "&qty=" <<
    		quantity << "&side=" << action << "&type=market&time_in_force=gtc";
		std::string params = ss.str();

    	std::string auth = ("APCA-API-KEY-ID: " + tools::Authentication::key);
		std::string secret = ("APCA-API-SECRET-KEY: " + tools::Authentication::key);
		std::vector<std::string> headers = {auth, secret};

		std::string apiResponse = tools::simplePost(url, "", params, headers);

#ifdef DEBUG
		std::cout << apiResponse << std::endl;
#endif

		// construct Order from JSON response
		rapidjson::Document doc = tools::getDOMTree(apiResponse);

		security = new Holding(doc["symbol"].GetString(), 
			doc["qty"].GetUint64(), doc["filled_avg_price"].GetDouble(),
			Holding::NASDAQ);

		timestamp = doc["filled_at"].GetString();

		tools::log("Filled order " + security->toString() + " at " + timestamp);
    }


}
