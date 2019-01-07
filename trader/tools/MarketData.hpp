// MarketData.hpp

#pragma once

#include <string>
#include <vector>

/**
 * A consolidated class for querying
 * the Tradier API for market data. 
 */
namespace tools
{
	class MarketData
	{
	public:
		// @param symbols - (i.e. "APPL", "AAPL150117C00440000", etc.)
		// @return current market prices of equities in symbols
		// NOTE: maximum 200 symbols at a time
		// NOTE: prices will come back sorted by symbol (ie. "AMZN" before "BA")
		// not same order as given in param symbols
		static std::vector<double> getPrices(const std::vector<std::string>& symbols);

		// @return if trading is open
		static bool isOpen();

		// TODO: https://iextrading.com/developer/docs/#relevant
		static double getRSI();

	private:
		// querying is very similar across other functions
		// @param endOfUrl - part of endpoint after /v1/markets/
		// @param symbols - comma delimited list of ticker symbols
		// @param otherHeaders - any other path parameters to add
		// @return whole response as string
		static std::string marketQuery
		(	
			const std::string& endOfUrl, 
			const std::vector<std::string>& symbols = std::vector<std::string>(),
			const std::vector<std::string>& otherParams = std::vector<std::string>()
		);
	};
}