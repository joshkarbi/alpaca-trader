// TestNetworkingUtilities


#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Main

#include <boost/test/unit_test.hpp>
#include "../tools/NetworkingUtilities.hpp"
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_networking_utilities)

BOOST_AUTO_TEST_CASE(simple_post)
{
    std::string post_test_url = "ptsv2.com/t/b8la9-1536326710/post";
    const std::string post_test_basic_auth = "test:test";
    
    const std::string response = tools::simplePost(post_test_url, post_test_basic_auth);
    
    // test simplePost works with test server
    BOOST_CHECK_EQUAL(response, "Thank you for this dump. I hope you have a lovely day!");
}
    
BOOST_AUTO_TEST_SUITE_END()
