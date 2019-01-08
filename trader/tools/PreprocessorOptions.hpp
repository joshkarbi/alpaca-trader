#include <exception>

// override rapidjson assertions to throw exceptions instead
// this is better 
#ifndef RAPIDJSON_ASSERT
#define RAPIDJSON_ASSERT(x) if(!(x)){ \
  throw std::runtime_error("ERROR: rapidjson internal assertion failure: " #x); }
#endif


// #define REAL

// all basically saying the same thing
// TODO: consolidate these to DEBUG
#define SANDBOX
#define PAPER
#define DEBUG_MODE
#define DEBUG

