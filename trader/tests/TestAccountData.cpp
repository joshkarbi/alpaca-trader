// TestAccountData.cpp

#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_account_data

#include "../tools/AccountData.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/FileReadingUtilities.hpp"
#include "../trading/Holding.hpp"

#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>

/**
 * There's no good way of testing this
 * besides checking for no throw and seeing API response.
 */
BOOST_AUTO_TEST_SUITE(test_account_data)

BOOST_AUTO_TEST_CASE(get_account_positions)
{
	// we need to set the access token first
	tools::Authentication::setup();

	std::vector<trading::Holding> holdings;

	BOOST_CHECK_NO_THROW(holdings = tools::AccountData::getAccountPositions());

	for (const trading::Holding& hold : holdings)
	{
		std::cout << hold.toString() << std::endl;
	}
}

BOOST_AUTO_TEST_SUITE_END()