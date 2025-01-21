#include "utils.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "err_list.hpp"
#include <sys/stat.h>





void get_conf()
{
	// Do stuf here
	// return settings struct...
}

void get_wol_pcs()
{
	// return struct...
}

void twol_init()
{
	std::ostringstream twol_dir;
  // std::string homeDir = std::getenv("HOME");
  struct stat dir_st;

  twol_dir << homeDir << "/.config/twol";
  std::string temp_conv = twol_dir.str();

  
  if(stat(temp_conv.c_str(), &dir_st) != 0)
  {	
  	if(mkdir(temp_conv.c_str(), 0777) == 0)
  	{
  		std::cout << "twol dir created\n";
  	}
  	else
  	{
  		std::cout << "twol dir failed!\n";
  	}
  }
  

	twol_dir << "/logs";
  std::string temp_str = twol_dir.str();

  if(stat(temp_str.c_str(), &dir_st) != 0)
  {
	  if(mkdir(temp_str.c_str(), 0777) == 0)
	  {
	  	std::cout << "logs dir created\n";
	  }
	  else
	  {
	  	std::cout << "failed to create logs dir\n";
	  }
	}
}
