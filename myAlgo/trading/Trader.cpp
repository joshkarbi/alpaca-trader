//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Trader.hpp"

#include "../tools/FileReadingUtilities.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include "../tools/NetworkingUtilities.hpp"
#include "../tools/PreprocessorOptions.hpp"
#include "../tools/Authentication.hpp"
#include "../tools/JSONUtilities.hpp"

#include "Strategy.hpp"

#include <fstream>
#include <iostream>
#include <ctime>

namespace trading
{
    // default constructor
    Trader::Trader()
    {
        findKeyID();
    }
    
    void Trader::initialize()
    {
        // setup Strategy
        assert(Strategy::setup());
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
    
    void Trader::findKeyID()
    {
        std::cout << "finding key id\n";

        rapidjson::Document doc = tools::getDOMTree(tools::getWholeFile(KEY_FILE));
        tools::Authentication::access_token = doc["paper-trading-id"].GetString();

        std::cout << "found token: " << tools::Authentication::access_token << std::endl;
    }

    const std::string Trader::KEY_FILE = "settings/key-id.txt";
}
