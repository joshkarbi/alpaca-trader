# Run using bash build.bash
# Add new .cpp files to link line below
# TODO: use CMake

# MAIN APPLICATION EXECUTABLE
g++ -std=c++11 -o trader.exe main.cpp trading/Order.cpp trading/Strategy.cpp trading/Holding.cpp trading/Trader.cpp trading/Stats.cpp tools/FileReadingUtilities.cpp tools/FileWritingUtilities.cpp tools/NetworkingUtilities.cpp -lcurl


# For TEST files (ie. using Boost Test) 
# add compiler flag "-I /usr/local/lib/boost_1_68_0"
# add linker flag "-L /usr/local/lib/boost_1_68_0/stage/lib"
# add flag -lboost_unit_test_framework
# RUN test files with --log_level=all argument

g++ tests/TestNetworkingUtilities.cpp -std=c++11 -o TestNetworkingUtilities.exe tools/NetworkingUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl

g++ tests/TestStrategy.cpp -std=c++11 -o TestStrategy.exe trading/Strategy.cpp tools/FileReadingUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl

g++ tests/TestFileReadingUtilities.cpp -std=c++11 -o TestFileReadingUtilities.exe tools/FileReadingUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl

g++ tests/TestJSONUtilities.cpp -std=c++11 -o TestJSONUtilities.exe tools/JSONUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -I/usr/local/lib/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl
