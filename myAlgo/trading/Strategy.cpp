// Strategy.cpp

#include "Strategy.hpp"

#include "FileReadingUtilities.hpp"
#include <cstddef>

namespace trading
{
	bool shouldBuy(const Order& buy)
	{
		bool result = false;

		// ... //

		return result;
	}

	bool shouldSell(const Order& sell)
	{
		bool result = false;

		// ... //

		return result;
	}

	bool setup(const std::string& fileName) 
	{
		if (fileExists(fileName)) 
		{
			std::vector<std::string> fileLines = getLines(fileName);
			for (std::string& line : fileLines) 
			{
				// split lines on space and insert key value
				size_t splitIndex = line.find_first_of(" ");
				while (splitIndex != std::string::npos)
  				{
    				std::string key = splitIndex.substr(0, splitIndex);
    				std::string value = splitIndex.substr(splitIndex);
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