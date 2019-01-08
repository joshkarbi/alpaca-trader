//
// An algorithmic trading application built to work with the
// Alpaca Markets brokerage API.
// 
// Main
// 

#include "trading/Trader.hpp"
#include "tools/FileWritingUtilities.hpp"

#include <fstream>

int main() 
{
	try 
	{
    	trading::Trader app;
    	app.run();
    	return 0;
    } catch (Exception e)
    {
    	// log any errors thrown up to main
    	log(e.what()+"\n");
    }
}
