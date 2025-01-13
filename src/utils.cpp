#include "utils.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <sys/stat.h>








void twol_init()
{
	// Gddfgdhfg
	std::ostringstream twol_dir;
  std::string homeDir = std::getenv("HOME");

  // if(homeDir)
  // {
  	twol_dir << homeDir << "/.config/twol";
  	std::string temp_conv = twol_dir.str();
  	// std::cout << twol_dir.str() << "\n";
  	if(mkdir(temp_conv.c_str(), 0777) == 0)
  	{
  		std::cout << "twol dir created\n";
  	}
  	else
  	{
  		std::cout << "twol dir failed!\n";
  	}
  // }
	
}
