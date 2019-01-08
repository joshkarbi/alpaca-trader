#include <exception>

// custom exception to be thrown instead of rapidjson calling exit() on program
// thanks to Matt Clarkson and the cereal serialization library
namespace custom
{
  struct RapidJSONException : Exception
  { RapidJSONException( const char * what_ ) : Exception( what_ ) {} };
}

// override rapidjson assertions to throw exceptions instead
// this is better 
#ifndef RAPIDJSON_ASSERT
#define RAPIDJSON_ASSERT(x) if(!(x)){ \
  throw ::custom::RapidJSONException("ERROR: rapidjson internal assertion failure: " #x); }
#endif

// #define REAL

// all basically saying the same thing
// TODO: consolidate these to DEBUG
#define SANDBOX
#define PAPER
#define DEBUG_MODE
#define DEBUG

