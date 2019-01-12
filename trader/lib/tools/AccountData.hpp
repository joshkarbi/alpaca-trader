// AccountData.hpp

#pragma once

#include "Authentication.hpp"
#include "NetworkingUtilities.hpp"
#include "PreprocessorOptions.hpp"
#include "JSONUtilities.hpp"
#include "../trading/Holding.hpp"

#include <string>
#include <vector>

namespace tools
{
	/**
	* Consolidated class for querying API
	* for User/Account data.
	*/
	class AccountData
	{
	public:
		// @return true if account is in ACTIVE state
		static bool accountIsActive()
		{
			std::string response = accountQuery("account");
			rapidjson::Document doc = getDOMTree(response);

			std::string activeState = "ACTIVE";
			return (doc["status"].GetString() == activeState);	
		}

		// @return cash available (run account query)
		static double updateCashBalance()
		{
			std::string response = accountQuery("account");
			rapidjson::Document doc = getDOMTree(response);

			cashInAccount = std::stod(doc["cash"].GetString());

			return cashInAccount;
		}

		// @return value of equities in account
		static double getEquityValue()
		{
			std::string response = accountQuery("account");
			rapidjson::Document doc = getDOMTree(response);

			return std::stod(doc["portfolio_value"].GetString()) - std::stod(doc["cash"].GetString());
		}

		// This will need to be done on start-up
		// @return list of all holdings - return nullptr if none
		// NOTE: Holding objects contain price, quantity, symbol, and exchange information
		static std::vector<trading::Holding> getAccountPositions()
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

		// @return price we paid for a stock
		// NOTE: returns -1 if we dont own the stock or order is not executed
		static double getPurchasePrice(const std::string& symbol)
		{
			constexpr double DEFAULT = -1;

			std::string response = accountQuery("positions");

			rapidjson::Document doc = getDOMTree(response);

			for (auto& positionObj : doc.GetArray())
			{
				if (positionObj["symbol"].GetString() == symbol)
				{
				// i.e. order not excuted yet
					if (positionObj["avg_entry_price"].IsNull()) { return DEFAULT; }

					return std::stod(positionObj["avg_entry_price"].GetString());
				}
			}

			return DEFAULT;
		}

		// returns the saved double amount, (DOES NOT FETCH NEW AMOUNT)
		static double getCashBalance()
		{
			// run query if not saved yet
			if (cashInAccount == -1) { updateCashBalance(); }
			return cashInAccount;
		}

	private:
		// @param endOfUrl - portion of endpoint after /v1/
		// @return response from API
		static std::string accountQuery(const std::string& endOfUrl)
		{
			std::string auth = ("APCA-API-KEY-ID: " + Authentication::key);
			std::string secret = ("APCA-API-SECRET-KEY: " + Authentication::secretKey);
			std::vector<std::string> headers = {auth, secret};

			std::string url = PAPER_DOMAIN+endOfUrl;

			return (simpleGet(url, "", headers));
		}

		// as described
		static double cashInAccount;

		static std::vector<trading::Holding> portfolio;
	};

	// for linking
	double AccountData::cashInAccount;
	std::std::vector<trading::Holding> portfolio;
}