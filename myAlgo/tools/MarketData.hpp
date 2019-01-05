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
		static std::vector<double> getPrices(const std::vector<std::string>& symbols);

		// @return if trading is open
		static bool isOpen();

	private:
		// querying is very similar across other functions
		// @param endOfUrl - part of endpoint after /v1/markets/
		// @return whole response as string
		static std::string marketQuery(const std::string& endOfUrl, const std::vector<std::string>& symbols = std::vector<std::string>());
	};
}