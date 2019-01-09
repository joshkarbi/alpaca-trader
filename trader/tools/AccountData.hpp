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

		// @return cash available (run account query)
		static double updateCashBalance();

		// @return value of equities in account
		static double getEquityValue();

		// This will need to be done on start-up
		// @return list of all holdings - return nullptr if none
		// Note: Holding objects contain price, quantity, symbol, and exchange information
		static std::vector<trading::Holding> getAccountPositions();

		// @return price we paid for a stock
		// Note: returns -1 if we dont own the stock
		static double getPurchasePrice(const std::string& symbol);

		// returns the saved double amount, (DOES NOT FETCH NEW AMOUNT)
		static double getCashBalance();

	private:
		// @param endOfUrl - portion of endpoint after /v1/
		// @return response from API
		static std::string accountQuery(const std::string& endOfUrl);

		// as described
		static double cashInAccount;

		static std::vector<trading::Holding> portfolio;
	};
}