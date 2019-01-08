# Run using bash build.bash
# Add new .cpp files to link line below
# TODO: use CMake

# MAIN APPLICATION EXECUTABLE
echo "Main executable"
g++ -O main.cpp -std=c++11 -o trader.exe trading/Order.cpp trading/Strategy.cpp trading/Holding.cpp trading/Trader.cpp trading/Stats.cpp tools/FileReadingUtilities.cpp tools/FileWritingUtilities.cpp tools/JSONUtilities.cpp tools/NetworkingUtilities.cpp tools/MarketData.cpp tools/AccountData.cpp tools/Authentication.cpp -lcurl -I /usr/local/lib/boost_1_68_0/ -I/usr/local/lib/


# For TEST files (ie. using Boost Test) 
# add compiler flag "-I /usr/local/lib/boost_1_68_0"
# add linker flag "-L /usr/local/lib/boost_1_68_0/stage/lib"
# add flag -lboost_unit_test_framework
# RUN test files with --log_level=all argument
echo "TestNetworkingUtilities"
g++ tests/TestNetworkingUtilities.cpp -std=c++11 -o TestNetworkingUtilities.exe tools/NetworkingUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl

echo "TestStrategy"
g++ tests/TestStrategy.cpp -std=c++11 -o TestStrategy.exe trading/Strategy.cpp tools/FileReadingUtilities.cpp tools/JSONUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl -I /usr/local/lib/boost_1_68_0/ -I/usr/local/lib/

echo "TestFileReadingUtilities"
g++ tests/TestFileReadingUtilities.cpp -std=c++11 -o TestFileReadingUtilities.exe tools/FileReadingUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl

echo "TestJSONUtilities"
g++ tests/TestJSONUtilities.cpp -std=c++11 -o TestJSONUtilities.exe tools/JSONUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -I/usr/local/lib/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl

echo "TestMarketData"
g++ tests/TestMarketData.cpp -std=c++11 -o TestMarketData.exe tools/MarketData.cpp tools/FileWritingUtilities.cpp tools/Authentication.cpp tools/JSONUtilities.cpp tools/NetworkingUtilities.cpp tools/FileReadingUtilities.cpp -I /usr/local/lib/boost_1_68_0/ -I/usr/local/lib/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl

echo "TestOrder"
g++ tests/TestOrder.cpp -std=c++11 -o TestOrder.exe tools/Authentication.cpp tools/FileWritingUtilities.cpp tools/FileReadingUtilities.cpp tools/JSONUtilities.cpp tools/NetworkingUtilities.cpp trading/Order.cpp trading/Holding.cpp -I /usr/local/lib/boost_1_68_0/ -I/usr/local/lib/ -L /usr/local/lib/boost_1_68_0/stage/lib/ -lboost_unit_test_framework -lcurl
