// Authentication.cpp

#include "Authentication.hpp"

#include "JSONUtilities.hpp"
#include <stdexcept>

namespace tools
{
	void Authentication::fetchNewAuthCode()
	{
		// GET https://api.tradier.com/v1/oauth/authorize
		// with params: client_id=<app key>&scope=trade&state=<any random string>
		const std::string url = https://api.tradier.com/v1/oauth/authorize

		// this invokes a shell command to open a chrome window 
		// and redirect to Tradier front-end to register
		system("open -a \"Google Chrome\" " +url+"?client_id="+app_key+"&scope=trade&state=myAlgoTrader");

		/** From Tradier documentation:

			If the user authorizes your application, 
			a call will be made to the callback URL 
			registered with your application. 
			That callback will look something like:

			http://mycallbackurl.example.com?code={authcode}&state={state}

			code - Your authorization code
			state - The same unique string you sent in the request above
		*/
		
	}

	/**
	*  Done each day at market open.
	*/
	void Authentication::fetchNewAccessToken()
	{
		// POST to            https://api.tradier.com/v1/oauth/accesstoken
		// with parameters:   grant_type=authorization_code&code=<AUTH_CODE>
		const std::string url = "https://api.tradier.com/v1/oauth/accesstoken?grant_type=authorization_code&code=";

		// response is JSON
		std::string response = simplePost(url+auth_code);

		rapidjson::Document jsonWithToken = getDOMTree(response);

		access_token = jsonWithToken["access_token"];

		if(jsonWithToken["status"] != "approved")
		{
			throw std::runtime_error("Failed to fetch new Trader API access token.");
		}
	}
}