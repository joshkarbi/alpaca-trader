
#include <fstream>
#include "Trader.hpp"

using namespace trading;

int main(int argc, const char * argv[]) {
    Trader* app = new Trader();
    app->run();
    return 0;
}
