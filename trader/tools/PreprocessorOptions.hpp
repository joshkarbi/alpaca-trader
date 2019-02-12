#include <exception>

// override rapidjson assertions to throw exceptions instead
// this is better 
#ifndef RAPIDJSON_ASSERT
#define RAPIDJSON_ASSERT(x) if(!(x)){ \
  throw std::runtime_error("ERROR: rapidjson internal assertion failure: " #x); }
#endif

// required for paper trading vs. real url to be used
#define PAPER
// #define REAL

// toggle between regular and debug log files to be used
#define DEBUG

