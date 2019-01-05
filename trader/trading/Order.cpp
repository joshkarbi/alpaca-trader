//
//  Created by Joshua Karbi on 2018-08-28.
//

#include "Order.hpp"

#include <ctime>

namespace trading
{
    Order::Order(const Holding& hold)
    {
        security = hold;
        
        // set time to time in human-readable string form
        std::time_t num_time = std::time(nullptr);
        time = std::asctime(std::localtime(&num_time));
    }

}
