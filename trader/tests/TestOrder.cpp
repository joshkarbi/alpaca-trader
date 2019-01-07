// TestOrder.cpp

#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_order

#include "../trading/Order.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/FileReadingUtilities.hpp"

#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_order)

BOOST_AUTO_TEST_CASE(post_new_order)
{
	// we need to set the access token first
	tools::Authentication::setup();

	// test buying one share of apple (can reset w/ Alpaca website after)
	trading::Order apple("buy", "AAPL", 1);

	// if successful, this should have been logged to debug_trader.log
	std::string fileText = tools::getWholeFile("debug_trader.log");

	BOOST_CHECK(fileText.find("AAPL") != std::string::npos);
	std::cout << "LOGGED: " << fileText << std::endl;
}

BOOST_AUTO_TEST_CASE(get_list_of_orders)
{
	// we need to set the access token first
	tools::Authentication::setup();

	BOOST_CHECK_NO_THROW(trading::Order::getAllOrders()); 
}

BOOST_AUTO_TEST_SUITE_END()