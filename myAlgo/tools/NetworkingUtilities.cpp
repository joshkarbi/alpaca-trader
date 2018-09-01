//
//  Created by Joshua Karbi on 2018-09-01.
//

#include "NetworkingUtilities.hpp"
#include <stdlib.h>

namespace
{
    // libcurl callback
    size_t writefunc(void *ptr, size_t size, size_t nmemb, void* s)
    {
        char* newPart = (char *)malloc(size*nmemb);
        memcpy(&newPart, ptr, size*nmemb);
        
        char* concatenated = (char *)malloc(1 + strlen((char *)s) + size*nmemb);
        
        strcpy(concatenated, (char *)s);
        strcat(concatenated, newPart);
        
        // concatenated has old stuff (s) with new stuff (ptr)
        // redirect s to concatenated
        s = concatenated;
        
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
        char* s = (char *)malloc(1);
        
        if (curl)
        {
            
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ::writefunc);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)s);
            curl_easy_perform(curl);
            
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        
        return s;
    }
}
