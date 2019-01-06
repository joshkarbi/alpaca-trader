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
	// we need to set the access token first
	tools::Authentication::setup();

	// check Apple
	BOOST_CHECK_NO_THROW(tools::MarketData::getPrices({"AAPL"}));
	std::cout << "AAPL: " << tools::MarketData::getPrices({"AAPL"})[0] << std::endl;

	// check Boeing
	BOOST_CHECK_NO_THROW(tools::MarketData::getPrices({"BA"}));
	std::cout << "BA: " << tools::MarketData::getPrices({"BA"})[0] << std::endl;

	// check multiple stocks at once
	std::vector<double> prices;

	// MUST BE SORTED
	std::vector<std::string> stocks = {"AMZN", "AAPL", "BA", "VGT"};
	BOOST_CHECK_NO_THROW(prices = tools::MarketData::getPrices(stocks));

	for (size_t i = 0; i < prices.size(); i++)
	{
		std::cout << stocks[i] << " " << prices[i] << std::endl;
	}

	// there's no good way of confirming this is correct
	// so just output this and confirm there's no segfault or abort
	// in the JSON or time_t string parsing involved
	std::cout << "Market open? " << tools::MarketData::isOpen() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
