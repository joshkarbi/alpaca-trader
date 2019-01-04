// TestStrategy


#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_trade_strategy

#include <boost/test/unit_test.hpp>
#include "../trading/Strategy.hpp"
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_trade_strategy)


// Test parsing of config file with
// Tradier-supported holding parameters
BOOST_AUTO_TEST_CASE(file_parse)
{
    // run the parser -> should return true if file exists and parsing is successful
    // NOTE: file path is full here since executable is run from myAlgo/ directory
    BOOST_CHECK_EQUAL(trading::Strategy::setup("tests/resources/strategy.config"), true);

    // test parameters in config file
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("profit-margin"), "0.02");
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("min-market-cap"), "2");
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("max-allowable-loss-margin"), "0.1");
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("key"), "value");

    // test parameters not in file (getValue should return "NULL")
    BOOST_CHECK_EQUAL(trading::Strategy::getParamValue("fake-parameter"), "NULL");
}

BOOST_AUTO_TEST_SUITE_END()
