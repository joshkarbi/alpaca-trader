// SentimentAnalysis.hpp

#pragma once

#include <string>

namespace tools
{
	class SentimentAnalysis
	{
	public:
		// @return sentiment score from IBM Watson NLP API (-1.0 to +1.0)
		static double getSentimentScore(const std::string& textToAnalyze);
	};
}