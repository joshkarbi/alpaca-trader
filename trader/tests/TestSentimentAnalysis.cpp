// TestSentimentAnalysis.cpp

#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_watson_nlp_integration

#include "../tools/SentimentAnalysis.hpp"
#include "../tools/Authentication.hpp"

#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_watson_nlp_integration)

BOOST_AUTO_TEST_CASE(watson_api_check)
{
	// we need to set the access token first
	tools::Authentication::setup();

	std::string test1 = "Apple shares soar as new iPhone is announced.";
	std::string test2 = "Stocks tumble as trade talks continue.";

	double score1, score2;

	BOOST_CHECK_NO_THROW(score1 = tools::SentimentAnalysis::getSentimentScore(test1));
	BOOST_CHECK_NO_THROW(score2 = tools::SentimentAnalysis::getSentimentScore(test2));

	std::cout << "Score 1: " << score1 << std::endl;
	std::cout << "Score 2: " << score2 << std::endl;
}



BOOST_AUTO_TEST_SUITE_END()
