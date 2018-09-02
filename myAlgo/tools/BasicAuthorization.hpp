//
//  Created by Joshua Karbi on 2018-09-01.
//

#pragma once

#include <string>

namespace tools
{
    static inline bool is_base64(unsigned char c)
    {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }
    
    std::string base64_encode(unsigned char const* bytes_to_encode, size_t in_len);
}
