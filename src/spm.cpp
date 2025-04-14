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
// #include "globals.hpp"
#include "dbg_log.hpp"
#include "config.hpp"
#include "spm_list.hpp"


// SPMUtils spmUtils; // Moved to globals.hpp
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
  SPMDebug dbg;

#if defined(_WIN32) || defined(_WIN64)
  spmUtils.SetWinTerm();
#endif

  // Basic Logging test to stdout
  dbg.Log(SPMDebug::noType, "Init", "Log Test");
  dbg.Log(SPMDebug::Info, "Init", "Info Test");
  dbg.Log(SPMDebug::Success, "Init", "Success Test");
  dbg.Log(SPMDebug::Warn, "Init", "Warn Test");
  dbg.Log(SPMDebug::Err, "Init", "Err Test");

  std::cout << "\n\n\n\n";

  std::ostringstream mainDir;

  mainDir << SPMUtils::GetHomeDir() << "/.spm";

  dbg.Log(SPMDebug::Info, "Init", "Checking for '.spm' directory...");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    spmUtils.makeDir(mainDir.str());
    dbg.Log(SPMDebug::Info, "Init", "'.spm' directory created");
  }
  else
  {
    dbg.Log(SPMDebug::Success, "Init", "'.spm' directory found'");
  }

  mainDir << "/lists";

  dbg.Log(SPMDebug::Info, "Init", "Checking for '.spm/lists' directory...");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    dbg.Log(SPMDebug::Info, "Init", "'.spm/lists' directory created");
    spmUtils.makeDir(mainDir.str());
  }
  else
  {
    dbg.Log(SPMDebug::Success, "Init", "'.spm/list' directory found");
  }
  mainDir.str(""); // Reset the string content so it dosen't retain the previous directories
  mainDir.clear(); // And clear any lefrover errors

  
  // Reassign the home directory with the main directory + logs directory
  // Todo: This should be done based on the settings
  mainDir << SPMUtils::GetHomeDir() << "/.spm/logs";

  dbg.Log(SPMDebug::Info, "Init", "Checking for '.spm/logs' directory ...");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    dbg.Log(SPMDebug::Info, "Init", "'.spm/logs' directory created");
    spmUtils.makeDir(mainDir.str());
  }
  else
  {
    dbg.Log(SPMDebug::Success, "Init", "'.spm/logs' directory found");
  }

  mainDir.str("");
  mainDir.clear();
#ifdef __linux__
  mainDir << SPMUtils::GetHomeDir() << "/.spm/spm.ini";
#endif

#if defined(_WIN32) || defined(_WIN64)
  mainDir << SPMUtils::GetHomeDir() << "\\.spm\\spm.ini";
#endif
  if(!spmUtils.checkFile(mainDir.str()))
  {
	  defaultConfig.restrict_mode = true;
	  defaultConfig.restrict_timeout = true;
	  defaultConfig.pc_status_mpack = true;
	  defaultConfig.debug_log = false;
	  defaultConfig.rescrict_time_span = 8;
	  defaultConfig.port = 8080;
	  spmConf.Write(defaultConfig);
	}
	else
	{
	  dbg.Log(SPMDebug::Success, "Init", "'.spm/spm.ini' found");
    // Once found read its settings and store them into the config structure
    globalConf = spmConf.Read();
	}

	mainDir.str("");
	mainDir.clear();

  /*

  Temportarly deprecated due to future change of the list system
  
	mainDir << SPMUtils::GetHomeDir() << "/.spm/lists/main_list.ini";
	dbg.Log(SPMDebug::noType, "File path to list: ", mainDir.str());
	if(spmUtils.checkFile(mainDir.str()) == false)
	{
	  dbg.Log(SPMDebug::Warn, "No list has been found");
	}
	*/
  
}

void SPM::Terminate()
{
  SPMDebug dbg;
  dbg.Log(SPMDebug::Info,"Terminate", "Safe exiting SPM...");
  // This is where variables are freed, files closed and exit processes.
}





/*
Todo:
- Creating single include headers for use in custom projects



*/
