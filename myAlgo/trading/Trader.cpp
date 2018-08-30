//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Trader.hpp"
#include "tools/FileReadingUtilities.hpp"
#include "tools/Logger.hpp"

#include <cpr/cpr.h>
#include <fstream>

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
            return;
        }
    }
    
    void Trader::initialize()
    {
        std::string post_body = "grant_type=authorization_code&code=";
        post_body.append(auth_code);
        auto r = cpr::Post(cpr::Url{"https://api.tradier.com/v1/oauth/accesstoken"},
                           cpr::Header{{"Content-Type", "application/json"}},
                           cpr::Payload{{"grant_type","authorization_code"},
                                    {"code", auth_code} }
                          );
        
        std::string response = r.text;
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
