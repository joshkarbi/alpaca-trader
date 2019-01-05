// JSONUtilities.hpp

#pragma once

#include "rapidjson/document.h"
#include <string>

/**
 * Custom wrapper around rapidJSON library.
 * 
 * Once we have the DOM tree object,
 * we can reference items by their key or index:
 *
 * ie. doc["key"].GetString() or doc[1].GetInt()
 *
 * This should be compiled with -I/usr/local/lib/ flag
 * or -I<path-to-rapidjson-include-folder>
 */
namespace tools
{
	rapidjson::Document getDOMTree(const std::string& json);
}