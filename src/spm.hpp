#pragma once




#include <vector>

#include "config.hpp"
#include "spm_list.hpp"



class SPM
{
	public:

		
  SPMConfig::cfgStruct globalConf;
  std::vector<SPMList::computer> mainList; // Store the main list at first run

  
	void Init();
	void SaveCustomLogFile(std::string f); // To do
	void LoadCustomDevList(std::string f);
	void SaveCustomDevList(std::string f);
	void ReloadDevList();
	void Terminate();
};
