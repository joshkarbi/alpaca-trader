//
//  Created by Joshua Karbi on 2018-09-01.
//

#include "NetworkingUtilities.hpp"
#include <stdlib.h>

namespace
{
    size_t writefunc(void *ptr, size_t size, size_t nmemb, char* s)
    {
       // char* newPart;
       // memcpy(&newPart, ptr, size*nmemb);
        strcat(s, static_cast<char*>(ptr));
        
        return size*nmemb;
    }
}

namespace tools
{
    std::string simplePost(const std::string& url , const std::string& params)
    {
        CURL* curl;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        char* s = nullptr;
        
        if (curl)
        {
            
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ::writefunc);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, s);
            curl_easy_perform(curl);
            
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        
        return s;
    }
}
