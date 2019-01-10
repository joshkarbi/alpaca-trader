// Holding.cpp

#include "Holding.hpp"

#include <sstream>

namespace trading
{
    // main constructor
    Holding::Holding(const std::string& sym, size_t number, double price, const std::string& ex)
    : symbol(sym), exchange(ex), numShares(number), purchasePrice(price)
    {
        // do nothing
    }
    
    // do not take into account price or number of shares
    bool Holding::operator==(const Holding& other) const
    {
        if (symbol == other.getSymbol() && exchange == other.getExchange())
        {
            return true;
        }
        return false;
    }
    

    std::string Holding::toString() const
    {
        std::stringstream res;
        std::string p;

        if (purchasePrice == UNKNOWN_PRICE) 
        { 
            p = " UNKNOWN PRICE (order to be filled)."; 
        }
        else
        {
            p = std::to_string(purchasePrice);
        }

        res << numShares << " of " << symbol << " on the " << exchange << " @ "<< p;
        return res.str();
    }

}
