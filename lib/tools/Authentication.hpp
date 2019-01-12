// Authentication.hpp
// Take care of obtaining and saving access tokens

#pragma once

#include "NetworkingUtilities.hpp"

#include <string>

namespace tools
{
	/**
	* Small API for saving authentication keys.
	* Getters unneccesary since tokens are public static.
	*/
	class Authentication
	{
	public:
		// alpaca API keys
		static std::string key;
		static std::string secretKey;
		
		static const std::string KEY_FILE;

		// parse out token from settings file
		static void setup()
		{
			rapidjson::Document doc = tools::getDOMTree(tools::getWholeFile(KEY_FILE));
        	key = doc["paper-trading-id"].GetString();
        	secretKey = doc["secret-key"].GetString();

        	std::cout << "Found API key: " << key << std::endl;
        	std::cout << "Found secret key: " << secretKey << std::endl;
		}

		// check if we've already done this
		static bool alreadySetup() { return !key.empty(); }
	};

	// required for linking
	std::string Authentication::key = "";
	std::string Authentication::secretKey = "";
	const std::string Authentication::KEY_FILE = "settings/.key-id";
}