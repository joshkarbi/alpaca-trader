# Overview
An algorithmic trading application being written in C++ for small portfolios.
Is being built to work with the Tradier brokerage API.

# Building
The application can be running the following:
```
cd myAlgo/
bash build.bash
```

# Tests
Function suites are tested in Unit Tests under the tests/ directory (using C++ Boost Unit Test Framework).
To run a test after building project (ie. one for NetworkingUtilities):
```
./TestNetworkingUtilities.exe
```
Or to run all unit tests:
```
bash run-tests.bash
```

# Dependencies
Relies on the libcurl C networking library.
Install the library and compile with the -lcurl linker flag.
Refer to: https://github.com/curl/curl.

Also makes use of the Boost C++ library.
Refer to https://www.boost.org/ for download instructions.

There's a Flask callback for collection OAuth tokens.
Relies on Flask version 0.12.2
```
pip install flask==0.12.2
```

# Running
In one shell:
```
cd myAlgo/
./trader.exe
```
In another shell:
```
cd myAlgo/server/
flask run
```
