# Overview
A Linux algorithmic trading application and C++ Alpaca Markets client.
Uses the open IEX API to fetch stock financial information and current prices.

# Using this as a C++ Alpaca Markets client library
Required setup (parsing account details out of settings/.key-id):
```C++
trading::Authentication::setup();
```
Placing orders:
```C++
std::string symbol = "AAPL";
trading::Order* buyOrder = new trading::Order("buy", symbol, numSharesToBuy);
trading::Order* sellOrder = new trading::Order("sell", symbol, numSharesToSell);
```
Querying for market prices:
```C++
std::vector<std::string> stocks = {"AMZN", "AAPL", "BA", "VGT"};
std::vector<double> prices = tools::MarketData::getPrices(stocks);
```
Getting any key stats available from IEX API:
```C++
std::vector<std::string> interestedFields = {"marketcap", "dividendYield", "peRatioHigh"};
std::vector<double> keyStats = tools::MarketData::getKeyStats("AAPL", interestedFields);
```

# Running the Trader
After revising configuration and authentication settings and building the project (see below).
```bash
cd trader/
./trader.exe
```

# Manual mode
Orders can be manually cancelled or placed via the command-line by running the commands below. Users should then follow the application's on-screen instructions (i.e. will be asked for "buy", "sell", or "cancel", then for order-id (if cancelling) or for symbol and quantity.
```bash
cd trader/
./trader.exe manual
```

# Building
The application can be built by running the following:
```bash
cd trader/
bash build.bash
```

# Tests
Function suites are tested in Unit Tests under the tests/ directory (using C++ Boost Unit Test Framework).
To run a test after building project (ie. one for NetworkingUtilities):
```bash
cd trader/
./TestNetworkingUtilities.exe
```

# Dependencies
Relies on the libcurl C networking library, as well as C++ Boost (version 1.68+).
cURL headers should be installed in /usr/include/curl and Boost in /usr/local/lib/boost_<version> .
Refer to: https://github.com/curl/curl and https://www.boost.org/.

# Settings
A ".key-id" config file must be made under settings/ and formatted as following:
```
{
  "paper-trading-id":"{your Alpaca Markets key}",
  "secret-key":"{your Alpaca Markets secret key}"
}
```
Stocks.config contains the stocks you want to have the algorithm track. 
Currently set to the S&P 500 indexed companies, but this can be configured.
See trading/Strategy.hpp for formatting details.

Strategy.config contains parameters than can be adjusted (sell-when and buy-when parameters).
See trading/Strategy.hpp for details.
