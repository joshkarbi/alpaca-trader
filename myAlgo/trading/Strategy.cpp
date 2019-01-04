// Strategy.cpp

#include "Strategy.hpp"

#include "../tools/FileReadingUtilities.hpp"

#include <cstddef>
#include <boost/algorithm/string.hpp>

namespace trading
{
	bool Strategy::shouldBuy(const Order& buy)
	{
		bool result = false;

		// ... //

		return result;
	}

	bool Strategy::shouldSell(const Order& sell)
	{
		bool result = false;

		// ... //

		return result;
	}

	bool Strategy::setup(const std::string& params, const std::string& stocks) 
	{
		std::string paramFile = (params.empty()) ? PARAM_CONFIG_FILE : params;
		std::string stockFile = (stocks.empty()) ? WATCHLIST_CONFIG_FILE : stocks;
		
		if (tools::fileExists(paramFile) && tools::fileExists(stockFile)) 
		{
			std::vector<std::string> paramLines = tools::getLines(PARAM_CONFIG_FILE);
			std::vector<std::string> stockLines = tools::getLines(WATCHLIST_CONFIG_FILE);

			for (std::string& line : paramLines) 
			{
				// skip blank lines or lines starting with #
				if (line.empty() || line[0] == '#') { continue; }

				// split lines on space and insert key value
				size_t splitIndex = line.find_first_of(" ");
				if (splitIndex != std::string::npos)
  				{	
    				std::string key = line.substr(0, splitIndex);
    				std::string value = line.substr(splitIndex+1);
    				parameters.insert(parameters.begin(), std::pair<std::string, std::string>(key, value));
  				}
			}

			for (std::string& line : stockLines)
			{
				if (line.empty() || line[0] == '#') { continue; }
				
				std::vector<std::string> lineElements;

				boost::split(lineElements,line,boost::is_any_of(", "));

				Stock s(lineElements[0], lineElements[1], lineElements[2]);
				watchlist.push_back(s);
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}