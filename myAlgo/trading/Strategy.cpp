// Strategy.cpp

#include "Strategy.hpp"

#include "../tools/FileReadingUtilities.hpp"

#include <cstddef>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>

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

	// parse out key:value strategy parameters from file
	// also store list of stocks to track from config file
	bool Strategy::setup(const std::string& params, const std::string& stocks) 
	{
		std::string paramFile = (params.empty()) ? PARAM_CONFIG_FILE : params;
		std::string stockFile = (stocks.empty()) ? WATCHLIST_CONFIG_FILE : stocks;

		if (tools::fileExists(paramFile) && tools::fileExists(stockFile)) 
		{
			std::vector<std::string> paramLines = tools::getLines(paramFile);
			std::vector<std::string> stockLines = tools::getLines(stockFile);

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

    				boost::algorithm::trim(key);
    				boost::algorithm::trim(value);

    				parameters.insert(parameters.begin(), std::pair<std::string, std::string>(key, value));
  				}
			}

			for (std::string& line : stockLines)
			{
				if (line.empty() || line[0] == '#') { continue; }

				std::vector<std::string> lineElements;

				boost::split(lineElements,line,boost::is_any_of(","));
				boost::algorithm::trim(lineElements[0]);
				
				if (lineElements.size() == 1)
				{
					// just symbol
					Stock s(lineElements[0]);
					watchlist.push_back(s);
				}
				else if (lineElements.size() == 2)
				{
					// symbol, name specified
					boost::algorithm::trim(lineElements[1]);
					Stock s(lineElements[0], lineElements[1]);
					watchlist.push_back(s);
				}
				else
				{
					// symbol, name, industry
					boost::algorithm::trim(lineElements[1]);
					boost::algorithm::trim(lineElements[2]);
					Stock s(lineElements[0], lineElements[1], lineElements[2]);
					watchlist.push_back(s); 
				}
				
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	// are static
	const std::string Strategy::PARAM_CONFIG_FILE = "settings/strategy.config";
	const std::string Strategy::WATCHLIST_CONFIG_FILE = "settings/stocks.config";

	// for linking with static members
	std::map<std::string, std::string> Strategy::parameters;
	std::vector<Stock> Strategy::watchlist;

}