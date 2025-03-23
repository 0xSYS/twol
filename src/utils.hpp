#pragma once



#include <string>




class SPMUtils
{
	public:
	 // static std::string homeDir; // Deprecated
	std::string GetCurrentDate();
  static std::string GetHomeDir();
  void makeDir(std::string d);
  bool checkDir(std::string d);
  bool checkFile(std::string f);
#if defined(_WIN32) || defined(_WIN64)
  void SetWinTerm();
#endif
	
};
