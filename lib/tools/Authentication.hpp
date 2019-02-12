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

		// setter for key and secret key
		static void setKeys(const std::string& keyID, const std::string& secret) {
			key = keyID;
			secretKey = secret;
		}

		// check if we've already done this
		static bool alreadySetup() { return !key.empty(); }
	};

	// required for linking
	std::string Authentication::key = "";
	std::string Authentication::secretKey = "";
}