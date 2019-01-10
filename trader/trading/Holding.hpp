// Holding.hpp

#pragma once

#include <stdint.h>
#include <string>
#include <stddef.h>

namespace trading
{
    /**
     * A Holding is a security with a ticker symbol, 
     * exchange, number of shares, and purchase price.
     */
    class Holding
    {
    public:
        // ie. at time order is placed (until filled)
        static constexpr double UNKNOWN_PRICE = -1;
        
        // main constructor
        Holding(const std::string& sym, size_t qty, double price, const std::string& ex);
        
        // Getters
        std::string getSymbol() const { return symbol; };
        std::string getExchange() const { return exchange; };
        size_t getNumShares() const { return numShares; };
        double getPrice() const { return purchasePrice; };
        
        // @return string representation of holding
        std::string toString() const;

        // overloads
        bool operator==(const Holding& other) const;
        char operator[] (size_t index) const { return symbol[index]; };
        
    private:
        // private members
        std::string symbol;
        
        std::string exchange;
        
        size_t numShares;
        
        double purchasePrice;
    };

} // namespace

// overload hash method to store in unordered sets
namespace std {
    template <> struct hash<trading::Holding>
    {
        size_t operator()(const trading::Holding& x) const
        {
            std::hash<std::string> holdingHhash;
            return holdingHhash(x.getSymbol()+x.getExchange());
        }
    };
}
