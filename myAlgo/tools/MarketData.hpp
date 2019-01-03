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
	};
}