// TestMarketData.cpp

#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_market_data

#include "../tools/MarketData.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/FileReadingUtilities.hpp"

#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_market_data)

BOOST_AUTO_TEST_CASE(price_check)
{
	// we need to see the access token first
	tools::Authentication::access_token = tools::getLines("tests/resources/access_token.txt")[0];

	// check Apple
	BOOST_CHECK_NO_THROW(tools::MarketData::getPrice("AAPL"));
	std::cout << "AAPL: " << tools::MarketData::getPrice("AAPL") << std::endl;

	// check Boeing
	BOOST_CHECK_NO_THROW(tools::MarketData::getPrice("BA"));
	std::cout << "BA: " << tools::MarketData::getPrice("BA") << std::endl;

	// there's no good way of confirming this is correct
	// so just output this and confirm there's no segfault or abort
	// in the JSON or time_t string parsing involved
	std::cout << "Market open? " << tools::MarketData::isOpen() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
