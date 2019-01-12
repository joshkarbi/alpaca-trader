// TestStrategy


#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_trade_strategy

#include "../trading/Strategy.hpp"
#include "../trading/Stock.hpp"
#include "../trading/Order.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/PreprocessorOptions.hpp"

#include <string>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <unistd.h>

BOOST_AUTO_TEST_SUITE(test_trade_strategy)


// Test parsing of config file with
// Tradier-supported holding parameters
BOOST_AUTO_TEST_CASE(file_parse)
{
    // run the parser -> should return true if file exists and parsing is successful
    // NOTE: file path is full here since executable is run from myAlgo/ directory
    std::string strategyFile = "tests/resources/strategy.config";
    std::string stockFile = "tests/resources/stocks.config";

    BOOST_CHECK_NO_THROW(trading::Strategy::setup(strategyFile, stockFile));

    // 1. Test basic strategy parameters
    // test parameters in config file
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("sell-num-tests-met"), 1);
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("sell-RSI-over"), 70);
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("sell-profit-margin-over"), 0.1);

    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("buy-num-tests-met"), 6);
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("buy-RSI-below"), 37);
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("buy-min-market-cap"), 10);
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("buy-PE-greater-than"), 10);

    BOOST_CHECK_EQUAL(trading::Strategy::getMinCash(), 75.0);
    
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

BOOST_AUTO_TEST_CASE(check_should_buy)
{
    tools::Authentication::setup();

    bool result = false;
    BOOST_CHECK_NO_THROW(result = trading::Strategy::shouldBuy("AAPL"));
    std::cout << "Should buy AAPL? " << result << std::endl;

    BOOST_CHECK_NO_THROW(result = trading::Strategy::shouldBuy("BA"));
    std::cout << "Should buy BA? " << result << std::endl;
}

BOOST_AUTO_TEST_CASE(check_should_sell)
{
    // Strategy::shouldSell() will throw if we don't currently own a stock
    // so first buy a stock and then sell it
    trading::Order buyApple("buy", "AAPL", 1);

    // wait for order to execute
    usleep(1000);

    bool sell;
    BOOST_CHECK_NO_THROW(sell = trading::Strategy::shouldSell("AAPL"));

    std::cout << "Should sell AAPL? " << sell << std::endl;

    // sell once we're done
    trading::Order sellApple("sell", "AAPL", 1);
}
BOOST_AUTO_TEST_SUITE_END()
