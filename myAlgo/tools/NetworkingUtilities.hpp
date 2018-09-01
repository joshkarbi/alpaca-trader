//
//  Created by Joshua Karbi on 2018-09-01.
//

#pragma once

#include <curl/curl.h>
#include <string>

namespace tools
{
    std::string simplePost(const std::string& url , const std::string& params = "");
}
