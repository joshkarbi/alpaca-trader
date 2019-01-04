//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Trader.hpp"
#include "../tools/FileReadingUtilities.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/PreprocessorOptions.hpp"

#include <fstream>
#include <iostream>
#include <ctime>

namespace trading
{
    // default constructor
    Trader::Trader()
    {
        try
        {
            findClientID();
        } catch (const std::runtime_error& e)
        {
            tools::log(e.what());
        }
        std::string user_name, password;
        
        std::cout << "Enter username: ";
        std::cin >> user_name;
        std::cout << "Enter password: ";
        std::cin >> password;
        user_pass = user_name+":"+password;
            
        // write account info to file
        //tools::appendMessage(AUTH_CODE_FILE_PATH, user_pass);
        
        // We should ask for the app consumer key through console input
        // then fetch an auth_code and access_token (see tools/Authentication.hpp)
        
#ifdef SANDBOX
        api_url = "https://sandbox.tradier.com";
#endif
#ifdef REAL
        api_url = "https://api.tradier.com";
#endif
    }
    
    void Trader::initialize()
    {
        // setup Strategy
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
    
    void Trader::findClientID()
    {
        
    }

}
