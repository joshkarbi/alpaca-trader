// Holding.hpp

#pragma once

#include <stdint.h>
#include <string>
#include <stddef.h>

namespace trading
{
    /**
     * Used by Portfolio to keep track of current holdings.
     *
     * A Holding is a security with a ticker symbol, 
     * exchange, number of shares, and purchase price.
     */
    class Holding
    {
    public:
        // statics for exchanges
        static const size_t NYSE = 0;
        static const size_t NASDAQ = 1;
        static const size_t TSX = 2;

        static constexpr double UNKNOWN_PRICE = -1;
        
        // main constructor
        Holding(const std::string& sym, size_t number, double price, size_t ex=0);
        
        // getters
        std::string getSymbol() const { return symbol; };
        std::string getStringExchange() const;
        std::string toString() const;
        size_t getExchange() const { return exchange; };
        size_t getNumShares() const { return num_shares; };
        double getPrice() const { return purchase_price; };
        
        // operator overloads
        bool operator==(const Holding& other) const;
        char operator[] (size_t index) const { return symbol[index]; };
        
    private:
        // ie. "APPL"
        std::string symbol;
        
        // see above statics
        size_t exchange;
        
        size_t num_shares;
        
        double purchase_price;
    };
} // namespace

// overload hash method to store in unordered sets
namespace std {
    template <> struct hash<trading::Holding>
    {
        size_t operator()(const trading::Holding& x) const
        {
            // assume size_t is 32 bits (can be 64 as well)
            size_t result = (x.getExchange() << 24);
            result += (x[0] << 24);
            result += (x[1] << 16);
            result += (x[2] << 8);
            result += x[3];
            return result;
        }
    };
}
