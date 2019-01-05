// AccountData.cpp

#include "AccountData.hpp"
#include "Authentication.hpp"
#include "NetworkingUtilities.hpp"
#include "PreprocessorOptions.hpp"
#include "JSONUtilities.hpp"

namespace tools
{
	void AccountData::fetchAccountNumber()
	{
		
	}

	std::string AccountData::accountQuery(const std::string& endOfUrl)
	{
		if (account_number.empty()) { fetchAccountNumber(); }
		if (account_type.empty()) { fetchAccountType(); }

		std::string auth = ("APCA-API-KEY-ID: " + Authentication::key);
		std::string secret = ("APCA-API-SECRET-KEY: " + Authentication::key);
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
		rapidjson::Document doc = getDOMTree(response);

		// ... //

		return results;
	}

	void AccountData::fetchAccountType()
	{
		// ... //
	}

	std::string AccountData::account_number;
	std::string AccountData::account_type;
}