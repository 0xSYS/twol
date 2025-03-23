/*

Main Source file of SPM library
*/




#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>

#include <sys/stat.h>
#include <type_traits>

#if defined(_WIN32) || defined(_WIN64)
  #include <Windows.h>
  #include <direct.h>
#endif



#include "spm.hpp"
#include "utils.hpp"
#include "globals.hpp"
#include "dbg_log.hpp"
#include "config.hpp"
#include "spm_list.hpp"


SPMUtils spmUtils;
SPMConfig spmConf;
SPMList spmLst;


void SPM::Init()
{
  /*
  Steps:
  If runing on windows Set ansi escapes on windows terminal
  1) Check for .spm directory (linux / windows). If none of them exist create them
  2) Check for configuration file. If not existing create it. (Here the default configuration structure is assigned)
  3) Check for availavble lists of computers or / servers
  4) Parse the lists
  */

  SPMConfig::cfgStruct defaultConfig;

#if defined(_WIN32) || defined(_WIN64)
  spmUtils.SetWinTerm();
#endif

  std::ostringstream mainDir;

  mainDir << SPMUtils::GetHomeDir() << "/.spm";

  dbg.Log(SPMDebug::Info, "Checking for '.spm' directory...");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    spmUtils.makeDir(mainDir.str());
    dbg.Log(SPMDebug::Info, "'.spm' directory created");
  }

  mainDir << "./spm/lists";

  dbg.Log(SPMDebug::Info, "Checking for '.spm/lists' directory...");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    dbg.Log(SPMDebug::Info, "'.spm/lists' directory created");
    spmUtils.makeDir(mainDir.str());
  }
  mainDir.str(""); // Reset the string content so it dosen't retain the previous directories
  mainDir.clear(); // And clear any lefrover errors

  
  // Reassign the home directory with the main directory + logs directory
  // Todo: This should be done based on the settings
  mainDir << SPMUtils::GetHomeDir() << "/.spm/logs";

  dbg.Log(SPMDebug::Info, "Checking for '.spm/logs' directory ...");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    dbg.Log(SPMDebug::Info, "'.spm/logs' directory created");
    spmUtils.makeDir(mainDir.str());
  }

  mainDir.str("");
  mainDir.clear();

  mainDir << SPMUtils::GetHomeDir() << "/.spm/spm.ini";
  if(spmUtils.checkFile(mainDir.str()) == false)
  {
    defaultConfig.cli_mode = false;
	  defaultConfig.restrict_mode = true;
	  defaultConfig.restrict_timeout = true;
	  defaultConfig.pc_status_mpack = true;
	  defaultConfig.debug_log = false;
	  defaultConfig.rescrict_time_span = 8;

	  spmConf.Write(defaultConfig);
	}

	mainDir.str("");
	mainDir.clear();

	mainDir << SPMUtils::GetHomeDir() << "/.spm/lists/main_list.ini";
	if(spmUtils.checkFile(mainDir.str()) == false)
	{
	  dbg.Log(SPMDebug::Warn, "No list has been found");
	}
  
}

void SPM::Terminate()
{
  dbg.Log(SPMDebug::Info, "Safe exiting SPM...");
  // This is where variables are freed, files closed and exit processes.
}
