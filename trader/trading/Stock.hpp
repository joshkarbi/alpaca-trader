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
		Stock(const std::string& s, const std::string& c="UNSPECIFIED", const std::string& i="UNSPECIFIED")
		{
			symbol = s;
			company = c;
			industry = i;
		}

		std::string getSymbol() const { return symbol; }
		std::string getCompany() const { return company; }
		std::string getIndustry() const { return industry; }

	private:
		std::string symbol, company, industry;
	};
}