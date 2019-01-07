// Authentication.cpp

#include "Authentication.hpp"
#include "FileReadingUtilities.hpp"
#include "FileWritingUtilities.hpp"
#include "JSONUtilities.hpp"
#include "PreprocessorOptions.hpp"

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace tools
{
	// parse out token from settings file
	void Authentication::setup()
    {
        rapidjson::Document doc = tools::getDOMTree(tools::getWholeFile(KEY_FILE));
        key = doc["paper-trading-id"].GetString();

#ifdef DEBUG
        std::cout << "Found API key: " << key << std::endl;
#endif
    }

	// required for linking
	std::string Authentication::key = "";
	const std::string Authentication::KEY_FILE = "settings/key-id.txt";
}