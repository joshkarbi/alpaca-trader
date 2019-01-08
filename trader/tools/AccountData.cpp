// AccountData.cpp

#include "AccountData.hpp"
#include "Authentication.hpp"
#include "NetworkingUtilities.hpp"
#include "PreprocessorOptions.hpp"
#include "JSONUtilities.hpp"

namespace tools
{
	std::string AccountData::accountQuery(const std::string& endOfUrl)
	{
		std::string auth = ("APCA-API-KEY-ID: " + Authentication::key);
		std::string secret = ("APCA-API-SECRET-KEY: " + Authentication::secretKey);
		std::vector<std::string> headers = {auth, secret};

		std::string url = PAPER_DOMAIN+endOfUrl;

		return (simpleGet(url, "", headers));
	}

	double AccountData::getAccountCashBalance()
	{
		std::string response = accountQuery("account");
		rapidjson::Document doc = getDOMTree(response);

		return doc["cash"].GetDouble();
	}

	double AccountData::getEquityValue()
	{
		std::string response = accountQuery("acount");
		rapidjson::Document doc = getDOMTree(response);

		return doc["portfolio_value"].GetDouble() - doc["cash"].GetDouble();
	}

	std::vector<trading::Holding> AccountData::getAccountPositions()
	{
		std::vector<trading::Holding> results;

		std::string response = accountQuery("positions");

		if (response == "[]")
		{
			// no open positions
			return results;
		}

		rapidjson::Document doc = getDOMTree(response);
		for (auto& positionObj : doc.GetArray())
		{
			// const std::string& sym, size_t number, double price, size_t ex=0
			trading::Holding pos(positionObj["symbol"].GetString(), std::stoi(positionObj["qty"].GetString()),
				std::stod(positionObj["avg_entry_price"].GetString()), trading::Holding::NASDAQ);
			results.push_back(pos);
		}

		return results;
	}

}