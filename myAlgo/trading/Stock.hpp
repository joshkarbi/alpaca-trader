// Stock.hpp

#pragma once

#include <string>

/**
 * Represents a stock
 * Contains a symbol, name, industry
 */
namespace trading
{
	class Stock
	{
	public:
		Stock(const std::string& s, const std::string& c, const std::string& i="")
		{
			symbol = s;
			company = c;
			industry = i;
		}

		std::string getSymbol() { return symbol; }
		std::string getCompany() { return company; }
		std::string getIndustry() { return industry; }

	private:
		std::string symbol, company, industry;
	};
}