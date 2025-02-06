#include <iostream>
#include <sstream>
#include "ext_deps/inifile-cpp/inicpp.h"
#include "config.hpp"
#include "utils.hpp"






//Some boring functions that parse the config lol
//NotSoImportant tbh XDD


/*
Todo:
- Use .config directory to store the settings(/home/user/.twol/twol.conf)
*/
void twol_cfg_write(cfg cfg_out)
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

  out_path << homeDir << "/.twol/twol.conf"; // Concatenate strings to create the file path where the config is stored
  
  config.save(out_path.str()); // And save it with the file path and name formed earlier.
  //Do stuff here
}


cfg twol_cfg_read()
{
  cfg cfg_in; // Configuration structure
  ini::IniFile in_config;
  std::ostringstream in_path;
  
  in_path << homeDir << "/.twol/twol.conf"; // Create the file location of the config file
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
