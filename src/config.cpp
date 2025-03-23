#include <sstream>
#include <string>







#include "inc/inifile-cpp/inicpp.h"

#include "config.hpp"
#include "utils.hpp"



void SPMConfig::Write(cfgStruct cfg_out)
{
  ini::IniFile config;
  std::ostringstream out_path;

  // Structure filling
  config["Settings"]["pcStat"]  = cfg_out.pc_status_mpack;
  config["Settings"]["CLIMode"] = cfg_out.cli_mode;
  config["Settings"]["dbgLog"]  = cfg_out.debug_log;
  config["Restricted_session"]["autolink"]        = cfg_out.restrict_autolink;
  config["Restricted_session"]["restrictMode"]    = cfg_out.restrict_mode;
  config["Restricted_session"]["timeoutSession"]  = cfg_out.restrict_timeout;
  config["Restricted_session"]["timeoutTimeSpan"] = cfg_out.rescrict_time_span;

  out_path << SPMUtils::GetHomeDir() << "/.spm/spm.ini"; // Concatenate strings to create the file path where the config is stored
  
  config.save(out_path.str()); // And save it with the file path and name formed earlier.
  //Do stuff here
}

SPMConfig::cfgStruct SPMConfig::Read()
{
   cfgStruct cfg_in; // Configuration structure
  ini::IniFile in_config;
  std::ostringstream in_path;
  
  in_path << SPMUtils::GetHomeDir() << "/.spm/spm.conf"; // Create the file location of the config file
  in_config.setMultiLineValues(true); // Allow the ini parser to load the sections and fields line by line
  in_config.load(in_path.str()); // Then open the config file

  // Parse the specific fields from the settings section.
  cfg_in.pc_status_mpack = in_config["settings"]["pcStat"].as<bool>();
  cfg_in.cli_mode        = in_config["settings"]["CLIMode"].as<bool>();
  cfg_in.debug_log       = in_config["settings"]["dbgLog"].as<bool>();
  cfg_in.restrict_mode      = in_config["Restricted_session"]["restrictMode"].as<bool>();
  cfg_in.restrict_autolink  = in_config["Restricted_session"]["autolink"].as<bool>();
  cfg_in.restrict_timeout   = in_config["Restricted_session"]["timeoutSession"].as<bool>();
  cfg_in.rescrict_time_span = in_config["Restricted_session"]["timeoutTimeSpan"].as<int>();
 

  return cfg_in; // And return the structure containing the configuration options
}
