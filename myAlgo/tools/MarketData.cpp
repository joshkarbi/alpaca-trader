// MarketData.cpp

#include "MarketData.hpp"

#include "NetworkingUtilities.hpp"
#include "JSONUtilities.hpp"
#include "Authentication.hpp"
#include "PreprocessorOptions.hpp"

#include <vector>
#include <iostream>
#include <stdexcept>
#include <ctime>

namespace tools
{
	std::string MarketData::marketQuery(const std::string& endOfUrl)
	{
		std::string auth = ("Authorization: Bearer "+Authentication::access_token);

		std::string accept = "Accept: application/json";
		std::vector<std::string> headers = {auth, accept};

		// debug endpoint
		std::string url = ("https://sandbox.tradier.com/v1/markets/"+endOfUrl);

#ifdef  REAL
		// real endpoint
		url = ("https://api.tradier.com/v1/markets/"+endOfUrl);
#endif

		return (simpleGet(url, "", headers));
	}

	double MarketData::getPrice(const std::string& symbol)
	{
		std::string tradierResponse = marketQuery("quotes?symbols="+symbol);
		rapidjson::Document domTree = getDOMTree(tradierResponse);

		// return avg between bid and ask
		if (domTree["quotes"]["quote"]["last"].IsDouble())
		{
			return (domTree["quotes"]["quote"]["last"].GetDouble());
		}
		else
		{
			throw std::runtime_error("Failed to parse Tradier API response: " + tradierResponse);
		}
	}

	bool MarketData::isOpen()
	{
		// first check using local time (to prevent rate limiting)
        std::time_t now = std::time(NULL);
		std::tm * ptm = std::localtime(&now);
		char buffer[32];

		// Format: Mo, 15.06.2009 20:20:00
		std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm); 
		std::cout << buffer;
		if (buffer[0] == 'S')
		{
			// Saturday or Sunday
			return false;
		}
		else if ( (buffer[16] == 0 && buffer[17] < '9') || (buffer[18] == 0 && buffer[19] == '9' && buffer[19] < '3')
		 || (buffer[16] == '1' && buffer[17] >= '6') || buffer[16] =='2')
		{
			// outside 09:30 to 16:00
			return false;
		}

  		// query if necessary
		std::string response = marketQuery("clock");
		rapidjson::Document domTree = getDOMTree(response);
		std::string state = domTree["clock"]["state"].GetString();
		if (state != "open")
		{
			return false;
		}
		return true;
	}
}