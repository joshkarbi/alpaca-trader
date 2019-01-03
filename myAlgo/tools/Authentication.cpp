// Authentication.cpp

#include "Authentication.hpp"
#include "FileReadingUtilities.hpp"
#include "FileWritingUtilities.hpp"
#include "JSONUtilities.hpp"

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <string.h>

namespace tools
{
	void Authentication::fetchNewAuthCode()
	{
		// GET https://api.tradier.com/v1/oauth/authorize
		// with params: client_id=<app key>&scope=trade&state=<any random string>
		const std::string url = "https://api.tradier.com/v1/oauth/authorize";

		// unique state string
		unsigned seed = time(0);
		srand(seed);
		std::string uniqueString = "";
		for(int i = 0; i < 10; i++)
		{
			uniqueString.append(1, 'a' + rand()%26);
		}

		// this invokes a shell command to open a chrome window 
		// and redirect to Tradier front-end to register
		std::string command = "open -a \"Google Chrome\" " +url+"?client_id="+app_key+"&scope=trade&state=" + uniqueString;
		system(command.c_str());

		// after registeration Tradier will hit our Flask API
		// which will write the info to auth.txt
		// (this is bad but the code expires in 10 minutes)
		// TODO: change this
		std::vector<std::string> fileLines;
		do
		{
			fileLines = getLines("../auth.txt");
		} while (fileLines.empty());
		rapidjson::Document jsonWithCode = getDOMTree(fileLines[0]);
		auth_code = jsonWithCode["code"].GetString();
		std::string state = jsonWithCode["state"].GetString();

		// check for unsafe condition
		if (state != uniqueString)
		{
			throw std::runtime_error("Tradier access token failed due to 'state' variable being malformed.");
		}

		// finally delete contents from auth.txt
		update("../auth.txt", "");
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

		access_token = jsonWithToken["access_token"].GetString();


		std::string app = "approved";
		std::string status = jsonWithToken["status"].GetString();
		if(strncmp(status.c_str(), app.c_str(), 8) != 0)
		{
			throw std::runtime_error("Failed to fetch new Trader API access token.");
		}
	}

	// required for linking
	std::string Authentication::access_token = "";
	std::string Authentication::auth_code = "";
	std::string Authentication::app_key = "";

}