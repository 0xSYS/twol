#include <chrono>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include <sys/stat.h>

#include "err_list.hpp"
#include "config.hpp"
#include "utils.hpp"








// Simple function that returns a string only the current date
// Pattern: Day - Month - Year
// Todo: (Optional) Allow custom patterns of the current date
std::string get_current_date()
{
  std::ostringstream temp;
  auto cd = std::chrono::system_clock::now();
  std::time_t current_dt = std::chrono::system_clock::to_time_t(cd);
  std::tm local_tm =*std::localtime(&current_dt);
  temp << std::put_time(&local_tm, "%d.%m.%Y");
  return temp.str();
}

// When called it looks for the configuration file and the wake on lan list as well as the restricted wake on lan list
void twol_init()
{
	std::ostringstream twol_dir;
  // No longer needed bc it was moved to utils.hpp
  struct stat dir_st; // Not sure but I think this is for storing the output return of the stat() function

  cfg default_config;

  // Merge the home directory path with the /home/user/.twol (The location where the settings and the lists are stored on linux)
  twol_dir << homeDir << "/.twol";

  // Here's a funny string conversion
  std::string temp_conv = twol_dir.str(); // String stream -> c++ string -> c string so it can be used with some C api too XDD

  // Next step: Directory setup
  if(stat(temp_conv.c_str(), &dir_st) != 0) // Check if the "twol" directory exists.
  {	
  	if(mkdir(temp_conv.c_str(), 0777) == 0) // If not create the "twol" directory and also check for success or failure
  	{
  		// Todo: the string array from err_list.hpp should be used for both writing the log to file and for frontend debug in the status bar
  		std::cout << "twol dir created\n";
  	}
  	else
  	{
  		std::cout << "twol dir failed!\n";
  	}
  }
  
  // Use the same directory path formed earlier (at line 36) to create the logs directory.
  // This is where most of the logs will be written on linux
	twol_dir << "/logs";
  std::string temp_str = twol_dir.str(); // Again the same string conversion lol


  // From here are pretty much the same steps as earlier on line 42
  if(stat(temp_str.c_str(), &dir_st) != 0) // Check for the "logs" directory
  {
	  if(mkdir(temp_str.c_str(), 0777) == 0) // If it dosen't exist create it and check for success or failure
	  {
	  	std::cout << "logs dir created\n";
	  }
	  else
	  {
	  	std::cout << "failed to create logs dir\n";
	  }
	}


	// Assign the default configuration

	default_config.cli_mode = false;
	default_config.restrict_mode = true;
	default_config.restrict_timeout = true;
	default_config.pc_status_mpack = true;
	default_config.debug_log = false;
	default_config.rescrict_time_span = 8;

	/*
	Todo:
	- After checking for the required directories check the settings for CLI mode or tui mode
	*/
}


// That's it
// Not much going on lol
