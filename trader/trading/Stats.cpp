// Stats.cpp

#include "Stats.hpp"
#include "../tools/FileWritingUtilities.hpp"
#include <string>

namespace trading
{
    void Stats::logStats(const std::vector<Holding>& holdings) const
    {
        std::string log_message = "";
        for (const Holding& holding : holdings)
        {
            log_message.append(holding.getStringExchange() + ":" + holding.getSymbol() + "\n");
            log_message.append(std::to_string(holding.getNumShares()) + " shares at $" + std::to_string(holding.getPrice()) + "\n");
        }
        tools::log(log_message);
    }
}
