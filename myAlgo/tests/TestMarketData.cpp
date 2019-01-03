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
	std::cout << "AAPL: " << tools::MarketData::getPrice("AAPL");

	// check Boeing
	BOOST_CHECK_NO_THROW(tools::MarketData::getPrice("BA"));
	std::cout << "BA: " << tools::MarketData::getPrice("BA");
}

BOOST_AUTO_TEST_SUITE_END()
