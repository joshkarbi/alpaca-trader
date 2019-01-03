// Authentication.hpp
// Take care of obtaining and saving access tokens

#pragma once

#include "NetworkingUtilties.hpp"

#include <string>

namespace tools
{
	/**
	* Small API for fetching new tokens from Tradier.
	* Getters unneccesary since tokens are public static.
	*/
	class Authentication
	{
	public:
		// short-lived code expiring in 10 minutes
		// used to register app with Tradier API
		// after successful registering, this is useless
		// we now use the access_token
		static std::string auth_code;

		// expires in 24 hours (needs to be done each day at 9:30 AM)
		static std::string access_token;

		// constant for this application to register with an account
		// this should be set up on startup
		static std::string app_key;

		// Should be done once and only once after inputting app key on start-up.
		// 
		// Get the auth_code and then get an access_token.
		// Note: this API relies on the caller to call fetchNewAccessToken() after
		// @throw if return token is malformed
		void fetchNewAuthCode();

		// Should be done each day at market open.
		// @throw runtime_error if this fails
		void fetchNewAccessToken();
	};
}