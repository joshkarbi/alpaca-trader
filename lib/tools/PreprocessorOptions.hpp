#include <exception>

// override rapidjson assertions to throw exceptions instead
// this is better 
#ifndef RAPIDJSON_ASSERT
#define RAPIDJSON_ASSERT(x) if(!(x)){ \
  throw std::runtime_error("ERROR: rapidjson internal assertion failure: " #x); }
#endif

// REQUIRED FOR PAPER TRADING URL TO BE USED
#define PAPER

// #define REAL

// basic debug messages
#define DEBUG

// if you want more detailed messages and API JSON responses to be printed
// #define VERBOSE_DEBUG

