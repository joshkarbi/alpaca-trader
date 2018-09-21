// Strategy.hpp

#pragma once

#include "Order.hpp"

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

		private:
			// TODO: add a whole bunch of parameters supported by Tradier API
	};
}