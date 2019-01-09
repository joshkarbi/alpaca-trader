// Strategy.cpp

#include "Strategy.hpp"

#include "../tools/FileReadingUtilities.hpp"
#include "../tools/JSONUtilities.hpp"
#include "../tools/MarketData.hpp"
#include "../tools/AccountData.hpp"

#include <cstddef>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>

namespace trading
{
	bool Strategy::shouldBuy(const std::string& symbol)
	{
		// first check if we even have enough money or if we are under reserve cash
		double cashInAccount = tools::AccountData::getCashBalance();
		if (tools::MarketData::getPrices({symbol})[0] > cashInAccount || reserveCash >= cashInAccount)
		{
			return false;
		}

		double testsToMeet = getParamValue("buy-num-tests-met");

		// 1. RSI
		if (tools::MarketData::getRSI(symbol) <= getParamValue("buy-RSI-below"))
		{
			testsToMeet--;
		}

		std::vector<double> keyStats = tools::MarketData::getKeyStats(symbol, {"marketcap", "dividendYield", "ytdChangePercent"});
		double peRatio = tools::MarketData::getPE(symbol);

		// 2. P/E ratio
		if (peRatio >= getParamValue("buy-PE-greater-than") && peRatio <= getParamValue("buy-PE-less-than"))
		{
			testsToMeet--;
		}

		// 3. Market cap
		if (keyStats[0] >= getParamValue("buy-min-market-cap"))
		{
			testsToMeet--;
		}

		// 4. Dividend yield
		if (keyStats[1] >= getParamValue("buy-min-dividend"))
		{
			testsToMeet--;
		}

		// 5. YTD percentage change
		if (keyStats[2] >= getParamValue("buy-min-ytd-change"))
		{
			testsToMeet--;
		}

		return (testsToMeet<=0);
	}

	bool Strategy::shouldSell(const std::string& symbol)
	{
		double testsToMeet = getParamValue("sell-num-tests-met");

		// 1. RSI
		if (tools::MarketData::getRSI(symbol) >= getParamValue("sell-RSI-over"))
		{
			testsToMeet--;
		}

		// 2. Profit margin
		double paid = tools::AccountData::getPurchasePrice(symbol);
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

			// parse out buy conditions
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[0], strategyJSON["buy-when"]["num-tests-met"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[1], strategyJSON["buy-when"]["RSI-below"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[2], strategyJSON["buy-when"]["min-market-cap-billions"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[3], strategyJSON["buy-when"]["PE-greater-than"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[4], strategyJSON["buy-when"]["PE-less-than"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[5], strategyJSON["buy-when"]["min-dividend"].GetDouble()));
			parameters.insert(parameters.begin(), std::pair<std::string, double>(BUY_WHEN[6], strategyJSON["buy-when"]["min-ytd-change"].GetDouble()));
			
			// parse out reserve cash
			reserveCash = strategyJSON["min-cash"].GetDouble();

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


	const std::string Strategy::SELL_WHEN[] = 
	{"sell-num-tests-met", "sell-profit-margin-over", "sell-RSI-over", "sell-loss-tolerance"};
	const std::string Strategy::BUY_WHEN[] =
	{"buy-num-tests-met", "buy-RSI-below", "buy-min-market-cap", "buy-PE-greater-than", "buy-PE-less-than", "buy-min-dividend", "buy-min-ytd-change"};

	// for linking with static members
	std::map<std::string, double> Strategy::parameters;
	std::vector<Stock> Strategy::watchlist;
	double Strategy::reserveCash;

}