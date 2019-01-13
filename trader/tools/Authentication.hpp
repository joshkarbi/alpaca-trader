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
		
		// Watson API credentials for NLP
		static std::string watsonKey;
		
		static const std::string KEY_FILE;

		// parse out token from settings file
		static void setup();

		// check if we've already done this
		static bool alreadySetup() { return !key.empty(); }
	};
}