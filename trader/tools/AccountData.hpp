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
		// @return true if account is in ACTIVE state
		static bool accountIsActive();

		// @return cash available
		static double getCashBalance();

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
	};
}