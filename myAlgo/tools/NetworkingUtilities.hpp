//
//  Created by Joshua Karbi on 2018-09-01.
//

#pragma once

#include <curl/curl.h>
#include <string>
#include <vector>

namespace tools
{
    std::string simplePost(const std::string& url ,
                           const std::string& user_pass,
                           const std::string& params = "",
                           const std::vector<std::string>& headers = std::vector<std::string>());
}
