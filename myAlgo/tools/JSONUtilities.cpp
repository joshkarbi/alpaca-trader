// JSONUtilities.cpp

#include "JSONUtilities.hpp"

namespace tools
{
	// refer to: http://rapidjson.org/md_doc_tutorial.html
	rapidjson::Document getDOMTree(const std::string& json)
	{
		rapidjson::Document dom;
		dom.Parse(json.c_str());
		return dom;
	}
}