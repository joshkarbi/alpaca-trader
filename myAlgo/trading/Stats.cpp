//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Stats.hpp"
#include "../tools/Logger.hpp"
#include <string>

namespace trading
{
    void Stats::logStats(const Portfolio& port) const
    {
        std::string log_message = "";
        for (const Holding& holding : port.getHoldings())
        {
            log_message.append(holding.getStringExchange() + ":" + holding.getSymbol() + "\n");
            log_message.append(std::to_string(holding.getNumShares()) + " shares at $" + std::to_string(holding.getPrice()) + "\n");
        }
        tools::log(log_message);
    }
}
