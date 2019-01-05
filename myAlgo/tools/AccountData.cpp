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
		std::string auth = ("Authorization: Bearer "+Authentication::access_token);

		std::string accept = "Accept: application/json";
		std::vector<std::string> headers = {auth, accept};

		// debug endpoint
		std::string url = "https://sandbox.tradier.com/v1/user/profile";

#ifdef  REAL
		// real endpoint
		url = "https://api.tradier.com/v1/user/profile";
#endif

		std::string response = simpleGet(url, "", headers);
		rapidjson::Document doc = getDOMTree(response);
		account_number = doc["profile"]["account"]["account_number"].GetString();
	}

	std::string AccountData::accountQuery(const std::string& endOfUrl)
	{
		if (account_number.empty()) { fetchAccountNumber(); }
		if (account_type.empty()) { fetchAccountType(); }

		std::string auth = ("Authorization: Bearer "+Authentication::access_token);

		std::string accept = "Accept: application/json";
		std::vector<std::string> headers = {auth, accept};

		// debug endpoint
		std::string url = ("https://sandbox.tradier.com/v1/accounts/"+account_number+"/"+endOfUrl);

#ifdef  REAL
		// real endpoint
		url = ("https://api.tradier.com/v1/accounts/"+account_number+"/"+endOfUrl);
#endif

		return (simpleGet(url, "", headers));
	}

	double AccountData::getAccountCashBalance()
	{
		std::string response = accountQuery("balances");
		rapidjson::Document doc = getDOMTree(response);

		return doc["balances"]["total_cash"].GetDouble();
	}

	double AccountData::getEquityValue()
	{
		std::string response = accountQuery("balances");
		rapidjson::Document doc = getDOMTree(response);

		return doc["balances"]["equity"].GetDouble();
	}

	int AccountData::getPendingOrders()
	{
		std::string response = accountQuery("balances");
		rapidjson::Document doc = getDOMTree(response);

		return doc["balances"]["pending_orders_count"].GetInt();
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