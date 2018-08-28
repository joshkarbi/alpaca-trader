
#include <fstream>
#include "Trader.hpp"

using namespace trading;

int main(int argc, const char * argv[]) {
    Trader app;
    app.initialize();
    app.runTrader();
    app.finishUp();

    return 0;
}
