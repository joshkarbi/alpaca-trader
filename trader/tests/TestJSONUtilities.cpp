// TestJSONUtilities

#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_json_utilities

#include <boost/test/unit_test.hpp>
#include "../tools/JSONUtilities.hpp"
#include "rapidjson/error/en.h"
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_json_utilities)

// test rapidjson wrapper
BOOST_AUTO_TEST_CASE(test_parser)
{
	std::string json = "{\"key\":\"value\",\"bid\":195.34,\"array\":[6, 2, 3]}";
	rapidjson::Document doc = tools::getDOMTree(json);

	BOOST_CHECK_EQUAL(doc.HasParseError(), false);
	if (doc.HasParseError()) { 
    	fprintf(stderr, "\nError(offset %u): %s\n", (unsigned)doc.GetErrorOffset(), GetParseError_En(doc.GetParseError()));
	}

	BOOST_CHECK(doc.HasMember("key"));
	BOOST_CHECK(doc.HasMember("bid"));
	BOOST_CHECK(doc.HasMember("array"));

	BOOST_CHECK(doc["key"].IsString());
	BOOST_CHECK(doc["bid"].IsDouble());
	BOOST_CHECK(doc["array"].IsArray());

	BOOST_CHECK_EQUAL(doc["key"].GetString(), "value");
	BOOST_CHECK_EQUAL(doc["bid"].GetDouble(), 195.34);
	BOOST_CHECK_EQUAL(doc["array"][0].GetInt(), 6);
	BOOST_CHECK_EQUAL(doc["array"][1].GetInt(), 2);
	BOOST_CHECK_EQUAL(doc["array"][2].GetInt(), 3);
}

BOOST_AUTO_TEST_SUITE_END()