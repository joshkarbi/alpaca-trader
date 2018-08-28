
#include <fstream>
#include "Trader.hpp"

int main(int argc, const char * argv[]) {
    
    trading::Trader application;
    application.initialize();
    application.runTrader();
    application.finishUp();
    
    return 0;
}
