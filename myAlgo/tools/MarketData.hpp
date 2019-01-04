// MarketData.hpp

#pragma once

#include <string>

/**
 * A consolidated class for querying
 * the Tradier API for market data. 
 */
namespace tools
{
	class MarketData
	{
	public:
		// @param symbol - (i.e. "APPL", "AAPL150117C00440000", etc.)
		// @return current market price of equity
		static double getPrice(const std::string& symbol);

		// @return if trading is open
		static bool isOpen();

	private:
		// querying is very similar across other functions
		// @param endOfUrl - part of endpoint after /v1/markets/
		// @return whole response as string
		static std::string marketQuery(const std::string& endOfUrl);
	};
}