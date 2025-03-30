#include <sstream>
#include <vector>
#include "inc/inifile-cpp/inicpp.h"
#include "spm_list.hpp"
#include "utils.hpp"
#include "globals.hpp"


SPMUtils temp;


std::vector <SPMList::computer> SPMList::ReadComputerList()
{
  computer in;

  std::vector<computer> inList;

	ini::IniFile ini_list;
	std::ostringstream list_path;
	#ifdef __linux__
	list_path << SPMUtils::GetHomeDir() << "/.spm/list.ini"; // The path to the list of computers
	#endif

	#if defined(_WIN32) || defined(_WIN64)
	list_path << SPMUtils::GetHomeDir() << "\\.spm\\lists\\list.ini"; // The path to the list of computers
	#endif

	std::cout << "PATH: " << list_path.str() << "\n";

	if(!temp.checkFile(list_path.str()))
	{
		dbg.Log(SPMDebug::Err, "File not foun d errg");
	}
	else
	{

	ini_list.load(list_path.str());

//	in.index = ini_list["main"]["pcCount"].as<int>();

	std::ostringstream incrementalPcName;

	for(int i = 0; i < 3; i++)
	{
		incrementalPcName.str("");
		incrementalPcName.clear();
	  incrementalPcName << "PC_" << i;
		in.macAddr = ini_list[incrementalPcName.str()]["macAddres"].as<std::string>();
		in.broadcastIP = ini_list[incrementalPcName.str()]["BroadcastIP"].as<std::string>();
		in.name = ini_list[incrementalPcName.str()]["Name"].as<std::string>();
		in.defaultIP=ini_list[incrementalPcName.str()]["IP"].as<std::string>();
		//std::cout << "for " << incrementalPcName.str() << " " << in.defaultIP << " " << in.macAddr << "\n";
		inList.push_back(in);
	}
	}
  return inList;


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
