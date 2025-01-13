#include <sstream>



#include "twol_list.hpp"

#include "ext_deps/inifile-cpp/inicpp.h"



twol_list Read_PC_List()
{
	twol_list input_list;
	ini::IniFile ini_list;

	ini_list.load("pc_list.twol");

	input_list.pc_count = ini_list["main"]["pcCount"].as<int>();

	std::ostringstream incrementalPcName;

	for(int i = 1; i < input_list.pc_count; i++)
	{
	  incrementalPcName << "PC_" << i;
		ini_list[incrementalPcName.str()]["macAddres"] = input_list.mac_addr;
		ini_list[incrementalPcName.str()]["BroadcastIP"] = input_list.broadcast_ip;
		ini_list[incrementalPcName.str()]["Name"] = input_list.pcName;
		ini_list[incrementalPcName.str()]["IP"] = input_list.pcIp;
	}


	return input_list;
}

void Write_PC_List(twol_list out_pc_list)
{
	ini::IniFile out_list;
	ini::IniFile temp_read;

  // Temporary reading of pc list to ensure that each new section is ordered by number. (This helps to prevent the same section names to be written)
	out_pc_list.pc_count = temp_read["main"]["count"].as<int>();

	if(out_pc_list.pc_count != out_pc_list.pc_count+1)
	  out_pc_list.pc_count++;

	out_list["main"]["count"] = out_pc_list.pc_count; // Store the number of computers entered to be used latter on for reading all assigned computers.
  std::ostringstream incrementalPcName;
	incrementalPcName << "PC_" << out_pc_list.pc_count;
	out_list[incrementalPcName.str()]["macAddres"] = out_pc_list.mac_addr;
	out_list[incrementalPcName.str()]["BroadcastIP"] = out_pc_list.broadcast_ip;
	out_list[incrementalPcName.str()]["Name"] = out_pc_list.pcName;
	out_list[incrementalPcName.str()]["IP"] = out_pc_list.pcIp;

	out_list.save("pc_list.twol");
}
