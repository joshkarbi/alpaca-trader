// Strategy.cpp

#include "Strategy.hpp"

#include "../tools/FileReadingUtilities.hpp"
#include <cstddef>

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

	bool Strategy::setup(const std::string& fileName) 
	{
		if (tools::fileExists(fileName)) 
		{
			std::vector<std::string> fileLines = tools::getLines(fileName);
			for (std::string& line : fileLines) 
			{
				// skip blank lines or lines starting with #
				if (line.empty() || line[0] == '#') { continue; }

				// split lines on space and insert key value
				size_t splitIndex = line.find_first_of(" ");
				while (splitIndex != std::string::npos)
  				{
    				std::string key = line.substr(0, splitIndex);
    				std::string value = line.substr(splitIndex);
    				parameters.insert(parameters.begin(), std::pair<std::string, std::string>(key, value));
  				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}