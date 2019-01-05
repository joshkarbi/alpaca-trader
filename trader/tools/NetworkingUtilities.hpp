//
//  Created by Joshua Karbi on 2018-09-01.
//

#pragma once

#include "PreprocessorOptions.hpp"

#include <curl/curl.h>
#include <string>
#include <vector>

namespace tools
{

	// globals
#ifdef PAPER
	const std::string PAPER_DOMAIN = "https://paper-api.alpaca.markets/v1/";
#endif
#ifndef PAPER
	const std::string PAPER_DOMAIN = "https://api.alpaca.markets/v1/";
#endif
	const std::string MARKET_DATA_DOMAIN = "https://data.alpaca.markets/v1/";

    std::string simplePost(const std::string& url,
                           const std::string& user_pass = "",
                           const std::string& params = "",
                           const std::vector<std::string>& headers = std::vector<std::string>());
    
    std::string simpleGet(const std::string& url,
                          const std::string& user_pass = "",
                          const std::vector<std::string>& headers = std::vector<std::string>());
}
