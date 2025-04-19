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

#include <unistd.h>

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

#if defined(_WIN32) || defined(_WIN64)
  spmUtils.SetWinTerm();
#endif

  // Basic Logging test to stdout
#ifndef SKIP_INITIAL_LOG_TEST
  SPM_LOG(SPMDebug::Info, "Info Test");
  SPM_LOG(SPMDebug::Success, "Success Test");
  SPM_LOG(SPMDebug::Warn, "Warning Test");
  SPM_LOG(SPMDebug::Err, "Error test");
  std::cout << "\n\n\n\n";
#endif

  std::ostringstream mainDir;

  mainDir << SPMUtils::GetHomeDir() << "/.spm";

  SPM_LOG(SPMDebug::Info, "Checking for '.spm' directory");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    spmUtils.makeDir(mainDir.str());
    SPM_LOG(SPMDebug::Info, "'.spm' directory created");
  }
  else
  {
    SPM_LOG(SPMDebug::Success, "'.spm' directory found");
  }

  mainDir << "/lists";

  SPM_LOG(SPMDebug::Info, "Checking for '.spm/lists' directory...");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    spmUtils.makeDir(mainDir.str());
  }
  else
  {
    SPM_LOG(SPMDebug::Success, "'.spm/lists' directory found");
  }
  mainDir.str(""); // Reset the string content so it dosen't retain the previous directories
  mainDir.clear(); // And clear any lefrover errors

  
  // Reassign the home directory with the main directory + logs directory
  // Todo: This should be done based on the settings
  mainDir << SPMUtils::GetHomeDir() << "/.spm/logs";

  SPM_LOG(SPMDebug::Info, "Checking for '.spm/logs' directory");
  if(spmUtils.checkDir(mainDir.str()) == false)
  {
    SPM_LOG(SPMDebug::Info, "'.spm/logs' directory created");
    spmUtils.makeDir(mainDir.str());
  }
  else
  {
    SPM_LOG(SPMDebug::Success, "'.spm/logs' directory found");
  }

  mainDir.str("");
  mainDir.clear();
#ifdef __linux__
/*
What an idiot.
I spent almost 4 fucking hours trying to find out why my fronted wasn't working at all and I js foudn out I forgot to update the fucking file extensions (Down below)
GOD DAMN
*/
  mainDir << SPMUtils::GetHomeDir() << "/.spm/spm.conf";
#endif

#if defined(_WIN32) || defined(_WIN64)
  mainDir << SPMUtils::GetHomeDir() << "\\.spm\\spm.conf";
#endif
  SPM_LOG(SPMDebug::noType, "Main Directory: ", mainDir.str());
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
	else if(spmUtils.checkFile(mainDir.str()) == true)
	{
	  SPM_LOG(SPMDebug::Success, "'.spm/spm.conf' found");
    // Once found read its settings and store them into the config structure
    globalConf = spmConf.Read();
	}

	mainDir.str("");
	mainDir.clear();


#ifdef __linux__
	mainDir << SPMUtils::GetHomeDir() << "/.spm/lists/main_list.sls";
#endif

#if defined(_WIN32) || defined(_WIN64)
  mainDir << SPMUtils::GetHomeDir() << "\\.spm\\lists\\main_list.sls";
#endif

	SPM_LOG(SPMDebug::noType, "File path to list: ", mainDir.str());
	if(spmUtils.checkFile(mainDir.str()) == false)
	{
	  SPM_LOG(SPMDebug::Warn, "No main list has beed found");
	}
	else
	{
	  // Parse the main list
	}
	
  
}

void SPM::Terminate()
{
  SPM_LOG(SPMDebug::Info, "Safe exiting SPM");
  // This is where variables are freed, files closed and exit processes.
}





/*
Todo:
- Creating single include headers for use in custom projects



*/
