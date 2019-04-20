

cmake_minimum_required (VERSION 2.6)
project (AlpacaTrader)

FIND_PACKAGE( Boost 1.68 )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

SET(GCC_COVERAGE_LINK_FLAGS    "-I /usr/local/lib/boost_1_68_0/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -I/usr/local/lib/ -lboost_unit_test_framework -lcurl")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Main application
add_executable(trader.exe main.cpp)

# Unit tests
#add_executable(TestNetworkingUtilities.exe tests/TestNetworkingUtilities.cpp)