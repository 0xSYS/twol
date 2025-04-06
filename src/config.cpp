#include <sstream>
#include <string>







#include "dbg_log.hpp"
#include "inc/inifile-cpp/inicpp.h"

#include "config.hpp"
#include "utils.hpp"
// #include "globals.hpp"





void SPMConfig::Write(cfgStruct cfg_out)
{
  ini::IniFile config;
  std::ostringstream out_path;
  SPMDebug dbg;

  // Structure filling
  config["Settings"]["pcStat"]  = cfg_out.pc_status_mpack;
  // config["Settings"]["CLIMode"] = cfg_out.cli_mode; // No longer needed
  config["Settings"]["dbgLog"]  = cfg_out.debug_log;
  // config["Restricted_session"]["autolink"]        = cfg_out.restrict_autolink; // Still no ideea what that is lmaooo
  config["RestrictedSession"]["restrictMode"]    = cfg_out.restrict_mode;
  config["RestrictedSession"]["timeoutSession"]  = cfg_out.restrict_timeout;
  config["RestrictedSession"]["timeoutTimeSpan"] = cfg_out.rescrict_time_span;
  config["RemotePowerOptions"]["Port"] = cfg_out.port;

  out_path << SPMUtils::GetHomeDir() << "/.spm/spm.ini"; // Concatenate strings to create the file path where the config is stored
  
  config.save(out_path.str()); // And save it with the file path and name formed earlier.
  //Do stuff here
}

SPMConfig::cfgStruct SPMConfig::Read()
{
  cfgStruct cfg_in; // Configuration structure
  ini::IniFile in_config;
  std::ostringstream in_path;
  SPMDebug dbg;
#ifdef __linux__
  in_path << SPMUtils::GetHomeDir() << "/.spm/spm.ini"; // Create the file location of the config file
#endif

#if defined(_WIN32) || defined(_WIN64)
  in_path << SPMUtils::GetHomeDir() << "\\.spm\\spm.ini"; // Create the file location of the config file
#endif

std::cout << "READ PAth: " << in_path.str() << "\n";

  if(!spmUtils.checkFile(in_path.str()))
  {
    dbg.Log(SPMDebug::Err, "spm.ini not found !");
  }
  else
  {
    in_config.setMultiLineValues(true); // Allow the ini parser to load the sections and fields line by line

    in_config.load(in_path.str()); // Then open the config file

    cfg_in.debug_log = in_config["Settings"]["dbgLog"].as<bool>();
    cfg_in.pc_status_mpack = in_config["Settings"]["pcStat"].as<bool>();
    cfg_in.rescrict_time_span = in_config["Restricted_session"]["timeoutTimeSpan"].as<int>();
    cfg_in.restrict_timeout = in_config["Restricted_session"]["timeoutSession"].as<bool>();
    cfg_in.restrict_mode = in_config["Restricted_session"]["restrictMode"].as<bool>();
    cfg_in.port = in_config["RemotePowerOptions"]["Port"].as<bool>();

  }

  return cfg_in;
}
