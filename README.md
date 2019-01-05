# Overview
An algorithmic trading application being written in C++ for small portfolios.
Is being built to work with the Alpaca Markets paper trading API.

# Building
The application can be built by running the following:
```
cd trader/
bash build.bash
```

# Tests
Function suites are tested in Unit Tests under the tests/ directory (using C++ Boost Unit Test Framework).
To run a test after building project (ie. one for NetworkingUtilities):
```
cd trader/
./TestNetworkingUtilities.exe
```
Or to run all unit tests:
```
cd trader/
bash run-tests.bash
```

# Dependencies
Relies on the libcurl C networking library.
Refer to: https://github.com/curl/curl.

Also makes use of the Boost C++ library.
Refer to https://www.boost.org/ for download instructions.

# Settings
A "key-id.txt" config file must be made under settings/ and format as following:
```
{
  "paper-trading-id":"KEY"
}
```
Stocks.config contains the stocks you want to have the algorithm track. 
By default is set to the current S&P 500 companies. See trading/Strategy.hpp for formatting details.

Strategy.config contains parameters than can be adjusted. See trading/Strategy.hpp for details.

# Running
```
cd trader/
./trader.exe
```
