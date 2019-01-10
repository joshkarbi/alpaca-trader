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

	double AccountData::updateCashBalance()
	{
		std::string response = accountQuery("account");
		rapidjson::Document doc = getDOMTree(response);

		cashInAccount = std::stod(doc["cash"].GetString());

		return cashInAccount;
	}

	double AccountData::getEquityValue()
	{
		std::string response = accountQuery("account");
		rapidjson::Document doc = getDOMTree(response);

		return std::stod(doc["portfolio_value"].GetString()) - std::stod(doc["cash"].GetString());
	}

	std::vector<trading::Holding> AccountData::getAccountPositions()
	{
		std::string response = accountQuery("positions");

		std::vector<trading::Holding> results;
		if (response == "[]")
		{
			// no open positions -> empty vector
			return results;
		}

		rapidjson::Document doc = getDOMTree(response);

		for (auto& positionObj : doc.GetArray())
		{
			// const std::string& sym, size_t number, double price, size_t ex=0
			trading::Holding pos(positionObj["symbol"].GetString(), std::stoi(positionObj["qty"].GetString()),
				std::stod(positionObj["avg_entry_price"].GetString()), positionObj["exchange"].GetString());
			results.push_back(pos);
		}

		return results;
	}

	bool AccountData::accountIsActive()
	{
		std::string response = accountQuery("account");
		rapidjson::Document doc = getDOMTree(response);

		std::string activeState = "ACTIVE";
		return (doc["status"].GetString() == activeState);
	}

	double AccountData::getPurchasePrice(const std::string& symbol)
	{
		std::string response = accountQuery("positions");

		rapidjson::Document doc = getDOMTree(response);

		for (auto& positionObj : doc.GetArray())
		{
			if (positionObj["symbol"].GetString() == symbol)
			{
				return std::stod(positionObj["avg_entry_price"].GetString());
			}
		}

		return -1;
	}

	double AccountData::getCashBalance()
	{
		// run query if not saved yet
		if (cashInAccount == -1) { updateCashBalance(); }
		return cashInAccount;
	}

	// link and set default
	double AccountData::cashInAccount = -1;
	std::vector<trading::Holding> AccountData::portfolio = {};
}