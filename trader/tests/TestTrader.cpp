// TestTrader.cpp

#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_trading_app

#include "../trading/Trader.hpp"
#include "../trading/Stock.hpp"
#include "../trading/Order.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/PreprocessorOptions.hpp"

#include <string>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <unistd.h>

/**
 * There's no good way of testing the main app loop
 * since real-world errors will be logic-based..
 *
 * Anyways, test for throws on init
 * and see if some function outputs make sense.
 */

// global for test
trading::Trader app;

BOOST_AUTO_TEST_SUITE(test_trader)


BOOST_AUTO_TEST_CASE(app_init)
{
    BOOST_CHECK_NO_THROW(app.initialize());
}

BOOST_AUTO_TEST_CASE(calculate_shares_order)
{
	size_t buy, sell;
	BOOST_CHECK_NO_THROW(buy = app.getSharesToBuy("AAPL"));
	BOOST_CHECK_NO_THROW(sell = app.getSharesToSell("AAPL"));

	// should be WORTH around cashInAccount/(numberOfStocksToOwn)
	// if this fails could also be because Strategy was improperly/not setup
	std::cout << "Shares to buy: " << buy << std::endl;
	std::cout << "Shares to sell: " << sell << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
