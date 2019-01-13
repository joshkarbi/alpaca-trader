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

	// check multiple stocks at once
	std::vector<double> prices;

	std::vector<std::string> stocks = {"AMZN", "AAPL", "BA", "VGT"};
	BOOST_CHECK_NO_THROW(prices = tools::MarketData::getPrices(stocks));

	for (size_t i = 0; i < prices.size(); i++)
	{
		std::cout << stocks[i] << ": $" << prices[i] << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(market_is_open)
{
	bool result;

	// will throw on malformed JSON response
	BOOST_CHECK_NO_THROW(result = tools::MarketData::isOpen());

	std::cout << "Market open? " << result << std::endl;
}


BOOST_AUTO_TEST_CASE(IEX_key_stats)
{
	std::vector<double> keyStats;
	std::vector<std::string> interestedFields = {"marketcap", "dividendYield", "peRatioHigh", "peRatioLow"};

	BOOST_CHECK_NO_THROW(keyStats = tools::MarketData::getKeyStats("AAPL", interestedFields));

	// print results
	for (size_t i = 0; i < keyStats.size(); i++)
	{
		std::cout << interestedFields[i] << ": " << keyStats[i] << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(calculate_RSI)
{
	double rsi;

	BOOST_CHECK_NO_THROW(rsi = tools::MarketData::getRSI("AAPL"));

	std::cout << "RSI of AAPL: " << rsi << std::endl;
}

BOOST_AUTO_TEST_CASE(PE_ratio)
{
	double peRatio;
	BOOST_CHECK_NO_THROW(peRatio = tools::MarketData::getPE("AAPL"));
	std::cout << "PE of AAPL: " << peRatio << std::endl;
}

BOOST_AUTO_TEST_CASE(todays_change_in_percentage)
{
	double change;
	BOOST_CHECK_NO_THROW(change = tools::MarketData::getTodayChangePercentage("AAPL"));
	std::cout << "Today % change in AAPL: " << change << std::endl;
}

BOOST_AUTO_TEST_CASE(latest_headline)
{
	std::string aapl="aapl", ba="ba", mmm="mmm";
	BOOST_CHECK_NO_THROW(aapl = tools::MarketData::getLatestHeadline(aapl));
	BOOST_CHECK_NO_THROW(ba = tools::MarketData::getLatestHeadline(ba));
	BOOST_CHECK_NO_THROW(mmm = tools::MarketData::getLatestHeadline(mmm));

	std::cout << "Apple headline: " << aapl << std::endl;
	std::cout << "Boing headline: " << ba << std::endl;
	std::cout << "3M headline: " << mmm << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
