// Strategy.cpp

#include "Strategy.hpp"

#include "../tools/FileReadingUtilities.hpp"
#include "../tools/JSONUtilities.hpp"
#include "../tools/MarketData.hpp"
#include "../tools/AccountData.hpp"
#include "../tools/PreprocessorOptions.hpp"

#include <cstddef>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>

namespace
{
	void debugMessage(const std::string& message, double val=-1)
	{
#ifdef VERBOSE_DEBUG 
		if (val != -1)
			std::cout << message << " " << val << std::endl;
		else
			std::cout << message << std::endl;
#endif
	}
}
namespace trading
{
	bool Strategy::shouldBuy(const std::string& symbol)
	{
		// first check if we even have enough money or if we are under reserve cash
		double cashInAccount = tools::AccountData::getCashBalance();
		if (tools::MarketData::getPrices({symbol})[0] > cashInAccount || reserveCash >= cashInAccount || !tools::MarketData::isOpen())
		{
			return false;
		}

		double testsToMeet = getParamValue("buy-num-tests-met");

		// 1. RSI
		if (tools::MarketData::getRSI(symbol) <= getParamValue("buy-RSI-below"))
		{
			::debugMessage("RSI under set oversold condition");
			testsToMeet--;
		}

		std::vector<double> keyStats = tools::MarketData::getKeyStats(symbol, {"marketcap", "dividendYield", "ytdChangePercent"});
		double peRatio = tools::MarketData::getPE(symbol);

		// 2. P/E ratio
		if (peRatio >= getParamValue("buy-PE-greater-than") && peRatio <= getParamValue("buy-PE-less-than"))
		{
			::debugMessage("P/E within specified ratio.");
			testsToMeet--;
		}

		// 3. Market cap
		if (keyStats[0] >= getParamValue("buy-min-market-cap"))
		{
			::debugMessage("Maret cap greater than minimum: ", keyStats[0]);
			testsToMeet--;
		}

		// 4. Dividend yield
		if (keyStats[1] >= getParamValue("buy-min-dividend"))
		{
			::debugMessage("Dividend yield greater than specified minimum: " , keyStats[1]);
			testsToMeet--;
		}

		// 5. YTD percentage change
		if (keyStats[2] >= getParamValue("buy-min-ytd-change"))
		{
			::debugMessage("YTD percentage change: ", keyStats[2]);
			testsToMeet--;
		}

		return (testsToMeet<=0);
	}

	bool Strategy::shouldSell(const std::string& symbol)
	{
		// first check if market is even open
		if ( ! tools::MarketData::isOpen()) { return false; }
		
		double testsToMeet = getParamValue("sell-num-tests-met");

		// 1. RSI
		if (tools::MarketData::getRSI(symbol) >= getParamValue("sell-RSI-over"))
		{
			testsToMeet--;
		}

		// 2. Profit margin
		double paid = tools::AccountData::getPurchasePrice(symbol);
		if (paid == -1) 
		{
			// order has not executed yet so it does not show up in account positions
			return false;
		}

		double currentPrice = tools::MarketData::getPrices({symbol})[0];
		double margin = (currentPrice-paid)/paid;
		if (margin >= getParamValue("sell-profit-margin-over"))
		{
			testsToMeet--;
		}
		
		// 3. Loss tolerance
		if (margin <= getParamValue("sell-loss-tolerance"))
		{
			testsToMeet--;
		}
		return (testsToMeet<=0);
	}

	// parse out json strategy parameters from file
	// also store list of stocks to track from config file
	bool Strategy::setup(const std::string& params, const std::string& stocks) 
	{
		std::string paramFile = (params.empty()) ? PARAM_CONFIG_FILE : params;
		std::string stockFile = (stocks.empty()) ? WATCHLIST_CONFIG_FILE : stocks;

		if (tools::fileExists(paramFile) && tools::fileExists(stockFile)) 
		{
			rapidjson::Document strategyJSON = tools::getDOMTree(tools::getWholeFile(paramFile));
			std::vector<std::string> stockLines = tools::getLines(stockFile);

			// parse out sell-when conditions
			parameters.insert(parameters.begin(), std::pair<std::string, double>(SELL_WHEN[0], strategyJSON["sell-when"]["num-tests-met"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(SELL_WHEN[1], strategyJSON["sell-when"]["profit-margin-over"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(SELL_WHEN[2], strategyJSON["sell-when"]["RSI-over"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(SELL_WHEN[3], strategyJSON["sell-when"]["loss-more-than"].GetDouble()));
			std::cout << "SELL-WHEN conditions saved." << std::endl;

			// parse out buy conditions
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[0], strategyJSON["buy-when"]["num-tests-met"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[1], strategyJSON["buy-when"]["RSI-below"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[2], strategyJSON["buy-when"]["min-market-cap-billions"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[3], strategyJSON["buy-when"]["PE-greater-than"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[4], strategyJSON["buy-when"]["PE-less-than"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[5], strategyJSON["buy-when"]["min-dividend-yield"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[6], strategyJSON["buy-when"]["min-ytd-change"].GetDouble()));
			std::cout << "BUY-WHEN conditions saved." << std::endl;
			std::cout << "Parameter map filled!" << std::endl;

			// parse out reserve cash and stocks to own
			reserveCash = strategyJSON["min-cash"].GetDouble();
			std::cout << "Reserve cash saved." << std::endl;

			stocksToOwn = strategyJSON["stocks-to-own"].GetUint();
			std::cout << "Stocks to own parsed. " << std::endl;

			// parse out watchlist
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
					std::cout << lineElements[0] << std::endl;
					watchlist.push_back(s);
				}
				else if (lineElements.size() == 2)
				{
					// symbol, name specified
					boost::algorithm::trim(lineElements[1]);
					std::cout << lineElements[0] << std::endl;
					Stock s(lineElements[0], lineElements[1]);
					watchlist.push_back(s);
				}
				else
				{
					// symbol, name, industry
					boost::algorithm::trim(lineElements[1]);
					boost::algorithm::trim(lineElements[2]);
					std::cout << lineElements[0] << std::endl;
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


	const std::string Strategy::SELL_WHEN[] = 
	{"sell-num-tests-met", "sell-profit-margin-over", "sell-RSI-over", "sell-loss-tolerance"};
	const std::string Strategy::BUY_WHEN[] =
	{"buy-num-tests-met", "buy-RSI-below", "buy-min-market-cap", "buy-PE-greater-than", "buy-PE-less-than", "buy-min-dividend", "buy-min-ytd-change"};

	// for linking with static members
	std::map<std::string, double> Strategy::parameters;
	std::vector<Stock> Strategy::watchlist;
	double Strategy::reserveCash;
	size_t Strategy::stocksToOwn;


}