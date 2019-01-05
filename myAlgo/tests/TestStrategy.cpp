// TestStrategy


#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_trade_strategy

#include "../trading/Strategy.hpp"
#include "../trading/Stock.hpp"

#include <string>
#include <iostream>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_trade_strategy)


// Test parsing of config file with
// Tradier-supported holding parameters
BOOST_AUTO_TEST_CASE(file_parse)
{
    // run the parser -> should return true if file exists and parsing is successful
    // NOTE: file path is full here since executable is run from myAlgo/ directory
    std::string strategyFile = "tests/resources/strategy.config";
    std::string stockFile = "tests/resources/stocks.config";

    // check return value is true
    BOOST_CHECK_EQUAL(trading::Strategy::setup(strategyFile, stockFile), true);

    // 1. Test basic strategy parameters
    // test parameters in config file
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("profit-margin"), "0.02");
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("min-market-cap"), "2");
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("max-allowable-loss-margin"), "0.1");
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("key"), "value");

    // test parameters not in file (getValue should return "NULL")
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("fake-parameter"), "NULL");

    // 2. Test stocks.config parsing
    std::vector<trading::Stock>& watchlist = trading::Strategy::getWatchlist();

    // Specify symbol, name, and industry
    // Apple
    BOOST_CHECK_EQUAL(watchlist[0].getSymbol(), "AAPL");
    BOOST_CHECK_EQUAL(watchlist[0].getCompany(), "Apple Inc.");
    BOOST_CHECK_EQUAL(watchlist[0].getIndustry(), "Consumer Electronics");

    // Boeing
    BOOST_CHECK_EQUAL(watchlist[1].getSymbol(), "BA");
    BOOST_CHECK_EQUAL(watchlist[1].getCompany(), "Boeing Inc.");
    BOOST_CHECK_EQUAL(watchlist[1].getIndustry(), "Aerospace");

    // AT&T
    BOOST_CHECK_EQUAL(watchlist[2].getSymbol(), "T");
    BOOST_CHECK_EQUAL(watchlist[2].getCompany(), "AT&T Inc.");
    BOOST_CHECK_EQUAL(watchlist[2].getIndustry(), "Communication Services");

    // only symbol
    BOOST_CHECK_EQUAL(watchlist[3].getSymbol(), "VGT");
    BOOST_CHECK_EQUAL(watchlist[3].getCompany(), "UNSPECIFIED");
    BOOST_CHECK_EQUAL(watchlist[3].getIndustry(), "UNSPECIFIED");

    BOOST_CHECK_EQUAL(watchlist[4].getSymbol(), "TEST");
    BOOST_CHECK_EQUAL(watchlist[4].getCompany(), "UNSPECIFIED");
    BOOST_CHECK_EQUAL(watchlist[4].getIndustry(), "UNSPECIFIED");

    // symbol and name only
    BOOST_CHECK_EQUAL(watchlist[5].getSymbol(), "MMM");
    BOOST_CHECK_EQUAL(watchlist[5].getCompany(), "The 3M Company");
    BOOST_CHECK_EQUAL(watchlist[5].getIndustry(), "UNSPECIFIED");

    // spaces should be trimmed/ignored
    BOOST_CHECK_EQUAL(watchlist[6].getSymbol(), "STOCK");
    BOOST_CHECK_EQUAL(watchlist[6].getCompany(), "Name");
    BOOST_CHECK_EQUAL(watchlist[6].getIndustry(), "Manufacturing");
}

BOOST_AUTO_TEST_SUITE_END()
