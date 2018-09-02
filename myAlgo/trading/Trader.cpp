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
            
            // TODO: save to file after
            std::cout << "Enter authorization code: ";
            std::cin >> auth_code;
            std::cout << "Enter username: ";
            std::cin >> user_name;
            std::cout << "Enter password: ";
            std::cin >> password;
        }
    }
    
    void Trader::initialize()
    {
        const std::string params = "grant_type=authorization_code&code="+auth_code;
        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};
        std::string auth_info = user_name+":"+password;
        headers.push_back("Authentication: Basic " + tools::base64_encode(reinterpret_cast<unsigned char const*>(auth_info.c_str()), auth_info.size()));
        
        std::string response = tools::simplePost("https://sandbox.tradier.com/v1/oauth/accesstoken", params, headers);
        
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
