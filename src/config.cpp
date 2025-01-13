#include <iostream>
#include "ext_deps/inifile-cpp/inicpp.h"
#include "config.hpp"






//Some boring functions that parse the config lol
//NotSoImportant tbh XDD

void twol_cfg_write(cfg cfg_out)
{
  ini::IniFile config;
  config["settings"]["pcStat"] = cfg_out.pc_status_mpack;
  config.save("twol.conf");
  //Do stuff here
}


cfg twol_cfg_read()
{
  cfg cfg_in;
  ini::IniFile config;
  cfg_in.pc_status_mpack = config["settings"]["pcStat"].as<bool>();
  return cfg_in;
}
