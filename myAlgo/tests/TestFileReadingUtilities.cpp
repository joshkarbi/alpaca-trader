// TestFileReadingUtilties


#ifndef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_file_reading

#include <boost/test/unit_test.hpp>
#include "../tools/FileReadingUtilities.hpp"
#include <string>
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_file_reading)

// test file exists
BOOST_AUTO_TEST_CASE(file_exists)
{
    BOOST_CHECK_EQUAL(tools::fileExists("tests/resources/strategy.config"), true);
    BOOST_CHECK_EQUAL(tools::fileExists("tests/TestStrategy.cpp"), true);

    BOOST_CHECK_EQUAL(tools::fileExists("fakeFile.txt"), false);
}

BOOST_AUTO_TEST_CASE(get_file_lines)
{
	std::vector<std::string> fileLines = tools::getLines("tests/resources/strategy.config");
	BOOST_CHECK_EQUAL(fileLines.empty(), false);

	BOOST_CHECK_EQUAL(fileLines[0], "# Strategy test config");
}

BOOST_AUTO_TEST_SUITE_END()
