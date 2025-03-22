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


#if defined(_WIN32) || defined(_WIN64)
  #include <Windows.h>
  #include <direct.h>
#endif





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
void spm_init()
{
	std::ostringstream main_dir;
  // No longer needed bc it was moved to utils.hpp
  struct stat dir_st; // Not sure but I think this is for storing the output return of the stat() function

  cfg default_config;

  // Merge the home directory path with the /home/user/.twol (The location where the settings and the lists are stored on linux)
  main_dir << homeDir << "/.spm";

  // Here's a funny string conversion
  std::string temp_conv = main_dir.str(); // String stream -> c++ string -> c string so it can be used with some C api too XDD

  // Next step: Directory setup
  if(stat(temp_conv.c_str(), &dir_st) != 0) // Check if the "twol" directory exists.
  {
  	#if defined(__linux__)
  	  if(mkdir(temp_conv.c_str(), 0777) == 0) // If not create the "twol" directory and also check for success or failure
  	  {
  	  	// Todo: the string array from err_list.hpp should be used for both writing the log to file and for frontend debug in the status bar
  	  	std::cout << "main dir created '.spm'\n";
  	  }
  	  else
  	  {
  	  	std::cout << "main dir failed!\n";
  	  }
  	#elif defined(_WIN32) || defined(_WIN64)
  	  if(mkdir(temp_conv.c_str()) == 0) // If not create the "twol" directory and also check for success or failure
  	  {
  	  	// Todo: the string array from err_list.hpp should be used for both writing the log to file and for frontend debug in the status bar
  	  	std::cout << "main dir created '.spm'\n";
  	  }
  	  else
  	  {
  	  	std::cout << "spm dir failed!\n";
  	  }
  	#endif
  }
  
  // Use the same directory path formed earlier (at line 36) to create the logs directory.
  // This is where most of the logs will be written on linux
	main_dir << "/logs";
  std::string temp_str = main_dir.str(); // Again the same string conversion lol


  // From here are pretty much the same steps as earlier on line 42
  if(stat(temp_str.c_str(), &dir_st) != 0) // Check for the "logs" directory
  {
  	#if defined(__linux__)
	    if(mkdir(temp_str.c_str(), 0777) == 0) // If it dosen't exist create it and check for success or failure
	    {
	    	std::cout << "logs dir created\n";
	    }
	    else
	    {
	    	std::cout << "failed to create logs dir\n";
	    }
	  #elif defined(_WIN32) || defined(_WIN64)
	    if(mkdir(temp_str.c_str()) == 0) // If it dosen't exist create it and check for success or failure
	    {
	    	std::cout << "logs dir created\n";
	    }
	    else
	    {
	    	std::cout << "failed to create logs dir\n";
	    }
	  #endif
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


// Power on a pc by entering only the custom name or the automatic name
// Use case in CLI mode 
void spm_power_on(std::string name)
{
	/*
	Steps:
	1) Check if the pc exists in one of the lists (Both restricted and nom-restricted)
	2) Check if the name is custom or automatic (automatic names will be assigned with this naming pattern: pc_<indexed number>)
	3) Get mac addres and broadcast ip
	4) Send wake on lan magick packet
	*/
} 

// That's it
// Not much going on lol
