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
  config["settings"]["pcStat"] = cfg_out.pc_status_mpack;
  config["settings"]["CLIMode"] = cfg_out.cli_mode;
  config["settings"]["dbgLog"] = cfg_out.debug_log;
  config["settings"]["restrictAutolink"] = cfg_out.restrict_autolink;
  config["settings"]["restrictMode"] = cfg_out.restrict_mode;

  out_path << homeDir << "/.twol/twol.conf"; // Concatenate strings to create the file path where the config is stored
  
  config.save(out_path.str()); // And save it with the file path and name formed earlier.
  //Do stuff here
}


cfg twol_cfg_read()
{
  cfg cfg_in;
  ini::IniFile config;
  std::ostringstream in_path;
  // config.load(in_path.str());
  
  cfg_in.pc_status_mpack = config["settings"]["pcStat"].as<bool>();
  // cfg_in.cli_mode = config["settings"]["CLIMode"].as<bool>();
  // cfg_in.restrict_mode = config["settings"]["restrictMode"].as<bool>();
  // cfg_in.restrict_autolink = config["settings"]["restrictAutolink"].as<bool>();
  // cfg_in.debug_log = config["settings"]["dbgLog"].as<bool>();

  in_path << homeDir << "/.twol/twol.conf"; // Same thing as before

  // config.decode();

  // config.load(in_path.str()); // But now load the configuration file
  return cfg_in; // And return the structure containing the configuration options
}
