//
// An algorithmic trading application built to work with the
// Alpaca Markets brokerage API.
// 
// Main method -> no logic, just startup and log any errors

#include "trading/Trader.hpp"
#include "tools/FileWritingUtilities.hpp"
#include "tools/PreprocessorOptions.hpp"
#include "trading/Order.hpp"
#include "tools/Authentication.hpp"

#include <fstream>
#include <iostream>
#include <string.h>

int main(int argc, char **argv) 
{
    trading::Trader app;

    std::string manualMode = "manual";
    const size_t EQUAL = 0;
    if (argc > 1 && (strncmp(argv[1], manualMode.c_str(), manualMode.size()) == EQUAL))
    {
        app.runManualMode();
        return 0;
    }


    try 
    {
    	app.run();
    } catch (const std::exception& e)
    {
    	// log any errors thrown up to main
    	tools::log(e.what());
    	std::cout << "Logging: " << e.what() << std::endl;
    }

    return 0;
}
