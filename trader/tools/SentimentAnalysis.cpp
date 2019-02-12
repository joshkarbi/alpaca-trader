// SentimentAnalysis.cpp

#include "SentimentAnalysis.hpp"

#include "NetworkingUtilities.hpp"
#include "Authentication.hpp"
#include "JSONUtilities.hpp"
#include "PreprocessorOptions.hpp"
#include "OutputOptions.hpp"

#include <boost/algorithm/string/replace.hpp>
#include <iostream>

namespace tools
{	
	/**
	* Call to IBM Watson NLP API
	*/
	double SentimentAnalysis::getSentimentScore(const std::string& textToAnalyze)
	{
		std::string textWithSpacesAsPlusSigns = boost::algorithm::replace_all_copy(textToAnalyze, " ", "+");

		std::string url = (WATSON_DOMAIN+"analyze?version=2018-11-16&features=sentiment&text="+textWithSpacesAsPlusSigns);
		std::string authInfo = ("apikey:"+Authentication::watsonKey);
		std::string watsonResponse = simpleGet(url, authInfo);

		if (OutputOptions::isVerbose)
			std::cout << "Watson response: " << watsonResponse << std::endl;	

		rapidjson::Document doc = getDOMTree(watsonResponse);

		// 0 is "neutral" according to Watson
		constexpr double DEFAULT = 0;

		try {
			if (doc["sentiment"]["document"]["score"].IsNull()) { return DEFAULT; }
			else { return doc["sentiment"]["document"]["score"].GetDouble(); }
		} catch (const std::exception& e) {
			return DEFAULT;
		}
	}
}