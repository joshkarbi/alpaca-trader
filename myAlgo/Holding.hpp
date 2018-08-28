//
//  Holding.hpp
//  myAlgo
//
//  Created by Joshua Karbi on 2018-08-28.
//  Copyright © 2018 Joshua Karbi. All rights reserved.
//

#pragma once
#include <stdint.h>
#include <string>
#include <stddef.h>

namespace trading
{
    // one holding has only a few data points
    class Holding
    {
    public:
        static const size_t NYSE = 0;
        static const size_t NASDAQ = 1;
        static const size_t TSX = 2;
        
        Holding()
        {
            // do nothing
        };
        ~Holding()
        {
            // do nothing
        };
        
        // main constructor
        Holding(const std::string& sym, size_t ex)
        {
            symbol = sym;
            exchange = ex;
        }
        // GETTERS
        std::string getSymbol() const { return symbol; };
        size_t getExchange() const { return exchange; };
        
        // OVERLOADED OPERATORS
        bool operator==(const Holding& other) const;
        char operator[] (size_t index) const { return symbol[index]; };
        
    private:
        
        // ie. "APPL"
        std::string symbol;
        
        // see above statics
        size_t exchange;
        
        // in USD
        double purchase_price;
        
        int num_shares;
    };
}

// overload hash method to store in unordered sets
// returns a size_t representing combination of exchange and ticker symbol
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
