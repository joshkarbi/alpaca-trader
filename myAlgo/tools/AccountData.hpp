// AccountData.hpp

#pragma once

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
		static std::string account_number;
		static std::string account_type;

		// @return cash available
		static double getAccountCashBalance();

		// @return value of equities in account
		static double getEquityValue();

		// This will need to be done on start-up
		// @return list of all holdings
		// Note: Holding objects contain price, quantity, symbol, and exchange information
		static std::vector<trading::Holding> getAccountPositions();

	private:
		// @param endOfUrl - portion of endpoint after /v1/
		// @return response from API
		static std::string accountQuery(const std::string& endOfUrl);

		// Invoked by accountQuery if account_number is null
		static void fetchAccountNumber();
		static void fetchAccountType();
	};
}