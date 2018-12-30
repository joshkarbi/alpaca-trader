# Overview
An algorithmic trading application being written in C++ for small portfolios.
Is being built to work with the Tradier brokerage API.

# Building
The application can be running the following:
'''
cd myAlgo/
bash build.bash
'''

# Tests
Function suites are tested in Unit Tests under the tests/ directory (using C++ Boost Unit Test Framework).
To run a test after building project (ie. one for NetworkingUtilities):
'''
./TestNetworkingUtilities.exe
'''

# Dependencies
Relies on the libcurl C networking library.
Install the library and compile with the -lcurl linker flag.
Refer to: https://github.com/curl/curl.

Also makes use of the Boost C++ library.
Refer to https://www.boost.org/ for download instructions.
