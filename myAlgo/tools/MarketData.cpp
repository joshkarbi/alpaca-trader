// MarketData.cpp

#include "MarketData.hpp"

#include "NetworkingUtilities.hpp"
#include "JSONUtilities.hpp"
#include "Authentication.hpp"
#include "PreprocessorOptions.hpp"

#include <vector>
#include <iostream>
#include <stdexcept>

namespace tools
{
	double MarketData::getPrice(const std::string& symbol)
	{
		std::string auth = ("Authorization: Bearer "+Authentication::access_token);

		std::string accept = "Accept: application/json";
		std::vector<std::string> headers = {auth, accept};

		// debug endpoint
		std::string url = ("https://sandbox.tradier.com/v1/markets/quotes?symbols="+symbol);

#ifdef  REAL
		// real endpoint
		url = ("https://api.tradier.com/v1/markets/quotes?symbols="+symbol);
#endif

		std::string tradierResponse = simpleGet(url, "", headers);

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
}