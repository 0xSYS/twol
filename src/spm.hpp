#pragma once




#include <iostream>

#include "config.hpp"



class SPM
{
	public:
	// SPMConfig spmCfg;
  SPMConfig::cfgStruct globalConf;
	void Init();
	void Terminate();
};
