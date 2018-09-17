//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Trader.hpp"
#include "../tools/FileReadingUtilities.hpp"
#include "../tools/Logger.hpp"
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
        tools::appendMessage(AUTH_CODE_FILE_PATH, user_pass);
        
        
#ifdef SANDBOX
        api_url = "https://sandbox.tradier.com";
#endif
#ifdef REAL
        api_url = "https://api.tradier.com";
#endif
    }
    
    void Trader::initialize()
    {
        srand(time(NULL));
        
        // OBTAIN AUTHORIZATION CODE
        std::string unique_string = {(char)(rand()%35+65), (char)(rand()%35+65), (char)(rand()%35+65), (char)(rand()%35+65)};
        std::string url = api_url + "/v1/oauth/authorize?client_id=" + client_id + "&scope=trade&state=" + unique_string;
        
#ifdef DEBUG_MODE
        std::cout << "GET AUTH_CODE URL: " << url << std::endl;
#endif
        
        std::string reponse = tools::simpleGet(url);
        
        // EXCHANGE FOR ACCESS TOKEN
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
        // get user auth_code
        if ( ! tools::fileExists(AUTH_CODE_FILE_PATH))
        {
            throw std::runtime_error("ERROR: Cannot find authorization code file.");
        }
        else
        {
            // parse out the auth code
            client_id = tools::getLines(AUTH_CODE_FILE_PATH)[0];
            
#ifdef DEBUG_MODE
            std::cout << "FOUND CLIENT_ID: " << client_id << std::endl;
#endif
        }
    }

}
