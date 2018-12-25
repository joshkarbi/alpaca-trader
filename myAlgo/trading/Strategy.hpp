// Strategy.hpp

#pragma once

#include "Order.hpp"
#include <map>

namespace trading
{
	// TODO: read in JSON formatted parameters for strategy from file
	class Strategy
	{
		public:
			// @return true if order agrees with strategy
			bool shouldBuy(const Order& buy);

			// @return true if sell agrees with strategy
			bool shouldSell(const Order& sell);

			// @brief fill parameters map from config file
			// @return true on success, false on failure (ie. file does not exist)
			// Note: expects config file to be formatted with <param><space><value> on each line
			bool setup(const std::string& fileName);

		private:
			// contains key-value pairs of trading parameters and limits
			// ie. "buyLimit" -> "$500"
			std::map<std::string, std::string> parameters;
	};
}