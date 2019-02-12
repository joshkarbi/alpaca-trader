// OutputOptions.hpp

#pragma once

#include <string>
#include <vector>

namespace tools
{
	/**
	* Handle debug, verbose, and production output settings.
	*/
	class OutputOptions
	{
	public:
		// parse option out of file
		static void setup();

		static bool isDebug, isVerbose, isProduction;

		// path to settings file
		static const std::string OUTPUT_SETTINGS_FILE;
	};
}