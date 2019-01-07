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
	std::string MarketData::marketQuery(const std::string& endOfUrl,
	 const std::vector<std::string>& symbols, const std::vector<std::string>& otherParams)
	{
		std::string auth = ("APCA-API-KEY-ID: " + Authentication::key);
		std::string secret = ("APCA-API-SECRET-KEY: " + Authentication::key);
		std::vector<std::string> headers = {auth, secret};

		// used for pricing info
		std::string list = "";
		if ( ! symbols.empty())
		{
			for (size_t i = 0; i < symbols.size(); i++)
			{
				list = list+symbols[i];
				if (i != symbols.size()-1) { list = list+","; }
			}
		}

		// ie. for pricing
		std::string url = MARKET_DATA_DOMAIN+endOfUrl;
		if (! list.empty()) { url = url+"?symbols="+list;}
		
		if ( ! otherParams.empty())
		{
			for (const std::string& param : otherParams)
			{
				url = url+"&"+param;
			}
		}
		return (simpleGet(url, "", headers));
	}

	std::vector<double> MarketData::getPrices(const std::vector<std::string>& symbols)
	{
		const std::vector<std::string> otherParameters = {"limit=1"};

		std::vector<double> results;
		results.reserve(symbols.size());
		
		std::string tradierResponse = marketQuery("bars/minute", symbols, otherParameters);

		rapidjson::Document domTree = getDOMTree(tradierResponse);

		// parse out price for each stock and push to result vector
		for (const std::string& symbol : symbols)
		{
			// [0] means grab first price Bar object
			// ["c"] means grab closing price in past 1 minute (ie. price now)
			results.push_back(domTree[symbol.c_str()][0]["c"].GetDouble());
		}

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