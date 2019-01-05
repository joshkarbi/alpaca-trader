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
	std::string MarketData::marketQuery(const std::string& endOfUrl, const std::vector<std::string>& symbols)
	{
		std::string auth = ("APCA-API-KEY-ID: " + Authentication::key);
		std::string secret = ("APCA-API-SECRET-KEY: " + Authentication::key);
		std::vector<std::string> headers = {auth, secret};

		// used for pricing info
		if ( ! symbols.empty())
		{
			std::string list = "";
			for (size_t i = 0; i < symbols.size(); i++)
			{
				list = list+symbols[i];
				if (i != symbols.size()-1) { list = list+","; }
			}
			headers.push_back("symbols: "+list);
		}

		return (simpleGet(MARKET_DATA_DOMAIN+endOfUrl, "", headers));
	}

	std::vector<double> MarketData::getPrices(const std::vector<std::string>& symbols)
	{
		std::vector<double> results;
		results.reserve(symbols.size());
		
		std::string tradierResponse = marketQuery("bars/minute", symbols);
		rapidjson::Document domTree = getDOMTree(tradierResponse);

		// ... //

		// placeholder for now
		return results;
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
		return domTree["is_open"].GetBool();
	}
}