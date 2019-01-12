// NetworkingUtilities.hpp

#pragma once

#include "PreprocessorOptions.hpp"

#include <curl/curl.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <vector>

// thank you to libcurl example "getinmemory.c", Daniel Stenberg
// https://curl.haxx.se/libcurl/c/getinmemory.html
namespace
{
  struct MemoryStruct
  {
    char *memory;
    size_t size;
  };

  static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
  {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);

    if(mem->memory == NULL) {
            /* out of memory! */
      printf("not enough memory (realloc returned NULL)\n");
      return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
  }
}

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
  const std::string IEX_DOMAIN = "https://api.iextrading.com/1.0/";

    // @param url - url to POST to
    // @param user_pass - see HTTP basic authentication
    // @param params - ie. "param1=value&other=val"
    // @param headers - any HTTP headers to append to the POST
  std::string simplePost(const std::string& url,
   const std::string& user_pass = "",
   const std::string& params = "",
   const std::vector<std::string>& headers = std::vector<std::string>())
  {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    struct MemoryStruct chunk;
    chunk.memory = (char *)malloc(1);
    chunk.size = 0;
    struct curl_slist *header_list = NULL;

    if (curl)
    {

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
      if (!user_pass.empty())
        curl_easy_setopt(curl, CURLOPT_USERPWD, user_pass.c_str());
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);

      /* follow any redirects if we get back a 302 */
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
      struct curl_slist *header_list = NULL;

      for (size_t i = 0; i < headers.size(); i++)
      {
#ifdef VERBOSE_DEBUG
        std::cout << "Header " << i << " " << headers[i] << std::endl;
#endif
        header_list = curl_slist_append(header_list, headers[i].c_str());
      }
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

      curl_easy_perform(curl);

      curl_easy_cleanup(curl);
    }

        curl_slist_free_all(header_list); /* free the list again */
    curl_global_cleanup();

    std::string result(chunk.memory, chunk.size);

#ifdef VERBOSE_DEBUG
    std::cout << "POST URL: " << url << " with params: " << params << std::endl;
    std::cout << result << std::endl;
#endif

    return result;
  }

    // @param url - url to POST to
    // @param user_pass - see HTTP basic authentication
    // @param params - ie. "param1=value&other=val"
    // @param headers - any HTTP headers to append to the POST
  std::string simpleGet(const std::string& url,
    const std::string& user_pass = "",
    const std::vector<std::string>& headers = std::vector<std::string>())
  {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    struct MemoryStruct chunk;
    chunk.memory = (char *)malloc(1);
    chunk.size = 0;
    struct curl_slist *header_list = NULL;

    if (curl)
    {

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

      if (!user_pass.empty())
      {
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user_pass.c_str());
      }

      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
      struct curl_slist *header_list = NULL;

      for (size_t i = 0; i < headers.size(); i++)
      {
        header_list = curl_slist_append(header_list, headers[i].c_str());
      }

      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

      curl_easy_perform(curl);

      curl_easy_cleanup(curl);
    }

        curl_slist_free_all(header_list); /* free the list again */
    curl_global_cleanup();

    std::string result(chunk.memory, chunk.size);

#ifdef VERBOSE_DEBUG
    std::cout << "GET to " << url << std::endl;
    std::cout << "With headers: " << std::endl;
    for (const std::string& header : headers)
    {
      std::cout << header << std::endl;
    }
    std::cout << result << std::endl;
#endif
    return result;
  }

  std::string simpleDelete(const std::string& url,
    const std::vector<std::string>& headers = std::vector<std::string>())
  {
    struct MemoryStruct chunk;

    CURL *hnd = curl_easy_init();
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);

    struct curl_slist *header_list = NULL;

    for (size_t i = 0; i < headers.size(); i++)
    {
      header_list = curl_slist_append(header_list, headers[i].c_str());
    }

    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, header_list);

    CURLcode ret = curl_easy_perform(hnd);
    curl_easy_cleanup(hnd);

    std::string result(chunk.memory, chunk.size);
    return result;
  }
}
