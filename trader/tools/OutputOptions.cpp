// OutputOptions.cpp

#include "OutputOptions.hpp"

#include "FileReadingUtilities.hpp"
#include "JSONUtilities.hpp"

namespace tools
{
	// parse out mode from settings file
	void OutputOptions::setup()
    {
        rapidjson::Document doc = tools::getDOMTree(tools::getWholeFile(OUTPUT_SETTINGS_FILE));
        std::string selectedMode = doc["mode"].GetString();
        const std::string debug = "debug";
        const std::string verbose = "verbose";
        
        if (selectedMode == debug) {
        	isDebug = true;
        } else if (selectedMode == verbose) {
        	isVerbose = true;
        } else {
        	isProduction = true;
        }
    }

	// required for linking
	const std::string OutputOptions::OUTPUT_SETTINGS_FILE = "settings/output.config";
	bool OutputOptions::isDebug = false;
	bool OutputOptions::isVerbose = false;
	bool OutputOptions::isProduction = false;
}
