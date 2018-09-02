//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Trader.hpp"
#include "../tools/FileReadingUtilities.hpp"
#include "../tools/Logger.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/BasicAuthorization.hpp"

//#include "/cpr/cpr.h"
#include <fstream>
#include <iostream>

namespace trading
{
    // default constructor
    Trader::Trader()
    {
        try
        {
            findAuthCode();
        } catch (const std::runtime_error& e)
        {
            tools::log(e.what());
            std::string user_name, password;
            
            std::cout << "Enter authorization code: ";
            std::cin >> auth_code;
            std::cout << "Enter username: ";
            std::cin >> user_name;
            std::cout << "Enter password: ";
            std::cin >> password;
            std::string concatenated_auth_info = user_name+":"+password;
            
            // TODO: save to file after
            user_pass_encoded = tools::base64_encode(reinterpret_cast<unsigned char const*>(concatenated_auth_info.c_str()), concatenated_auth_info.size());
        }
        
#ifdef SANDBOX
        api_url = "https://sandbox.tradier.com";
#endif
#ifdef REAL
        api_url = "https://api.tradier.com";
#endif
    }
    
    void Trader::initialize()
    {
        const std::string params = "grant_type=authorization_code&code="+auth_code;
        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};
        headers.push_back("Authentication: Basic " + user_pass_encoded);
        
        std::string response = tools::simplePost(api_url+"/v1/oauth/accesstoken", params, headers);
        
        // TODO: parse response to get access token
    }

    void Trader::runTrader()
    {
        // get access token
        // query prices
        // change positions
        
        // update stats by appending to Orders vector
        // update portfolio (cash left and holdings)
    }

    void Trader::finishUp()
    {
        // write the trading day's stats to a file.
        // ie. trading_stats.logStats(file_path);
    }
    
    void Trader::findAuthCode()
    {
        // get user auth_code
        if ( ! tools::fileExists(AUTH_CODE_FILE_PATH))
        {
            throw std::runtime_error("ERROR: Cannot find authorization code file.");
        }
        else
        {
            // parse out the auth code
            auth_code = tools::getLines(AUTH_CODE_FILE_PATH)[0];
        }
    }

}
