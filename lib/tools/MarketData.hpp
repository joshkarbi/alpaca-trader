// MarketData.hpp

#pragma once

#include "NetworkingUtilities.hpp"
#include "JSONUtilities.hpp"
#include "Authentication.hpp"
#include "PreprocessorOptions.hpp"

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>
#include <vector>

namespace
{
	void debugMessage(const std::string& message)
	{
#ifdef VERBOSE_DEBUG
		std::cout << message << std::endl;
#endif		
	}
}

/**
 * A consolidated class for querying
 * the Tradier API for quotes and IEX API for stock data.
 */
 namespace tools
 {
 	class MarketData
 	{
 	public:
		// @param symbols - (i.e. "APPL", "AAPL150117C00440000", etc.)
		// @return current market prices of equities in symbols in same order
 		static std::vector<double> getPrices(const std::vector<std::string>& symbols)
 		{
 			std::vector<double> results;

 			for (const std::string& symbol : symbols)
 			{
 				std::string iexResponse = marketQueryIEX("stock/"+symbol+"/price");
 				
			// response is just a number (no JSON)
 				results.push_back(std::stod(iexResponse));
 			}

 			return results;
 		}

		// @return if trading is open
 		static bool isOpen()
 		{
			// first check using local time (to prevent rate limiting)
 			std::time_t now = std::time(NULL);
 			std::tm * ptm = std::localtime(&now);
 			char buffer[32];

		// Format: Mo, 15.06.2009 20:20:00
 			std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
 			if (buffer[0] == 'S')
 			{
			// Saturday or Sunday
 				return false;
 			}
 			else if ( (buffer[16] == 0 && buffer[17] < '9') || (buffer[18] == 0 && buffer[19] == '9' && buffer[19] < '3')
 				|| (buffer[16] == '1' && buffer[17] >= '6') || buffer[16] =='2')
 			{
			// outside 09:30 to 16:00
 				return false;
 			}

  		// query if necessary
 			std::string response = marketQueryAlpaca(PAPER_DOMAIN+"clock");
 			rapidjson::Document domTree = getDOMTree(response);
 			return domTree["is_open"].GetBool();
 		}

		// @return 14-day RSI for stock with ticker symbol equal to 'symbol'
 		static double getRSI(const std::string& symbol)
 		{
 			double numLosses = 0, totalLoss = 0, numGains = 0, totalGain = 0;

 			std::string iexResponse = marketQueryIEX("stock/"+symbol+"/chart/1m");
 			rapidjson::Document recentStats = getDOMTree(iexResponse);

 			constexpr size_t NUM_PERIODS = 14;
 			for (size_t i = 1; i <= NUM_PERIODS; i++)
 			{
 				double dayDelta = recentStats[recentStats.Size()-i]["changePercent"].GetDouble();

 				::debugMessage("Day " + std::to_string(i) + " changePercent: " + std::to_string(dayDelta));

 				if  (dayDelta < 0) 
 				{ 
 					numLosses++;
 					totalLoss += dayDelta;
 				}
 				else 
 				{ 
 					numGains++;
 					totalGain += dayDelta;
 				}
 			}
 			double avgGain = totalGain/numGains;
 			double avgLoss = (-1)*totalLoss/numLosses;

 			double denominator = 1.0+(avgGain*NUM_PERIODS + getCurrentGain(symbol))/(avgLoss*NUM_PERIODS + getCurrentLoss(symbol));
 			double rsi = (100.0 - (100.0)/denominator);

 			::debugMessage("RSI calculated for " + symbol + ": " + std::to_string(rsi));

 			return rsi;
 		}

		// get a bunch of key stats in one IEX query
		// @param fields - i.e. "marketcap", "dividendYield", "ytdChangePercent"
		// @throws on failure to parse api response
 		static std::vector<double> getKeyStats(const std::string& symbol, const std::vector<std::string>& fields = {})
 		{
 			std::vector<double> results;
 			results.reserve(fields.size());

 			std::string iexResponse = marketQueryIEX("stock/"+symbol+"/stats");
 			rapidjson::Document doc = getDOMTree(iexResponse);

 			for (const std::string& field : fields)
 			{
 				results.push_back(doc[field.c_str()].GetDouble());
 			}

 			return results;
 		}

		// @return today's percentage move
 		static double getTodayChangePercentage(const std::string& symbol)
 		{
 			std::string response = marketQueryIEX("stock/"+symbol+"/quote");
 			rapidjson::Document doc = getDOMTree(response);

 			constexpr double DEFAULT = 0;
 			if (doc["changePercent"].IsNull())
 			{
 				return DEFAULT;
 			}
 			double res = doc["changePercent"].GetDouble();

 			::debugMessage("Current change percent in " + symbol + ": " + std::to_string(res));
 			
 			return res;
 		}

		// @return P/E ratio
 		static double getPE(const std::string& symbol)
 		{
 			constexpr double DEFAULT = 0;

 			std::string response = marketQueryIEX("stock/"+symbol+"/quote");
 			rapidjson::Document doc = getDOMTree(response);

 			if ( doc["peRatio"].IsNull())
 			{
 				return DEFAULT;
 			}

 			return doc["peRatio"].GetDouble();
 		}

 	private:
		// querying is very similar across other functions
		// @param url - entire URL (sometimes data.api.markets, others paper-api...)
		// @param symbols - comma delimited list of ticker symbols
		// @param otherHeaders - any other path parameters to add
		// @return whole response as string
 		static std::string marketQueryAlpaca (	
 			std::string url, 
 			const std::vector<std::string>& symbols = std::vector<std::string>(),
 			const std::vector<std::string>& otherParams = std::vector<std::string>())
 		{
 			std::string auth = ("APCA-API-KEY-ID: " + Authentication::key);
 			std::string secret = ("APCA-API-SECRET-KEY: " + Authentication::secretKey);
 			std::vector<std::string> headers = {auth, secret};

		// used for pricing info
 			std::string list = "";
 			if ( ! symbols.empty())
 			{
 				for (size_t i = 0; i < symbols.size(); i++)
 				{
 					list = list+symbols[i];
 					if (i != symbols.size()-1) { list = list+","; }
 				}
 			}
 			
 			if ( ! otherParams.empty())
 			{
 				for (const std::string& param : otherParams)
 				{
 					url = url+"&"+param;
 				}
 			}
 			return (simpleGet(url, "", headers));
 		}

		// query the IEX open API
		// @param url after https://api.iextrading.com/1.0/
 		static std::string marketQueryIEX(const std::string& endOfUrl)
 		{
 			return (simpleGet(IEX_DOMAIN+endOfUrl));
 		}

		// opposites of each other
		// return change in percent from today
 		static double getCurrentGain(const std::string& symbol)
 		{
 			double percent = getTodayChangePercentage(symbol);
 			if (percent < 0) { return 0; }
 			return percent;
 		}
 		static double getCurrentLoss(const std::string& symbol)
 		{
 			double percent = getTodayChangePercentage(symbol);
 			if (percent > 0) { return 0; }
 			return percent;
 		}

 		// @return latest news headline related to stock with ticker 'symbol'
 		static std::string getLatestHeadline(const std::string& symbol)
		{
			// strings still not supported by constexpr
			const std::string DEFAULT = "";

			// is array of news objects
			std::string response = marketQueryIEX("stock/"+symbol+"/news/last/1");
			rapidjson::Document doc = getDOMTree(response);

			if (doc[0]["headline"].IsNull()) { return DEFAULT; }
			else { return doc[0]["headline"].GetString(); }
		}
 	};
 }