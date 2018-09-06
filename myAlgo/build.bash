# Run using bash ./build.bash
# Add new .cpp files to link line below

g++ -std=c++11 main.cpp trading/Order.cpp trading/Holding.cpp trading/Portfolio.cpp trading/Trader.cpp trading/Stats.cpp tools/BasicAuthorization.cpp tools/FileReadingUtilities.cpp tools/Logger.cpp tools/NetworkingUtilities.cpp -lcurl


# For TEST files (ie. using Boost Test) 
# include compiler flag "-I /usr/local/lib/boost_1_68_0"
# and linker flag "-L /usr/local/lib/boost_1_68_0/stage/lib"
