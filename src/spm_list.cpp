

#include <sstream>




#include "inc/inifile-cpp/inicpp.h"
#include "spm_list.hpp"
#include "utils.hpp"
#include "globals.hpp"





SPMList::computer SPMList::ReadComputerList()
{
  computer in;

	ini::IniFile ini_list;
	std::ostringstream list_path;
	list_path << SPMUtils::GetHomeDir() << "/.spm/list.ini"; // The path to the list of computers

	ini_list.load(list_path.str());

	in.index = ini_list["main"]["pcCount"].as<int>();

	std::ostringstream incrementalPcName;

	for(int i = 1; i < in.index; i++)
	{
	  incrementalPcName << "PC_" << i;
		ini_list[incrementalPcName.str()]["macAddres"] = in.macAddr;
		ini_list[incrementalPcName.str()]["BroadcastIP"] = in.broadcastIP;
		ini_list[incrementalPcName.str()]["Name"] = in.name;
		ini_list[incrementalPcName.str()]["IP"] = in.defaultIP;
	}

  return in;
}


void SPMList::WriteComputerList()
{
  ini::IniFile out_list;
	ini::IniFile temp_read;
	std::ostringstream list_path;
	list_path << SPMUtils::GetHomeDir() << "/.spm/list.ini"; // Same as before

  // Temporary reading of pc list to ensure that each new section is ordered by number. (This helps to prevent the same section names to be written)
	MainList.index = temp_read["main"]["count"].as<int>();

	if(MainList.index != MainList.index+1)
	  MainList.index++;

	out_list["main"]["count"] = MainList.index; // Store the number of computers entered to be used latter on for reading all assigned computers.
  std::ostringstream incrementalPcName;
	incrementalPcName << "PC_" << MainList.index;
	out_list[incrementalPcName.str()]["macAddres"] = MainList.macAddr;
	out_list[incrementalPcName.str()]["BroadcastIP"] = MainList.broadcastIP;
	out_list[incrementalPcName.str()]["Name"] = MainList.name;
	out_list[incrementalPcName.str()]["IP"] = MainList.defaultIP;

	out_list.save(list_path.str());
}
