#include <sstream>

#include "ext_deps/inifile-cpp/inicpp.h"

#include "spm_list.hpp"
#include "utils.hpp"

/*
This is where the assigned computers will get parsed with all necessary parameters (Mac addres, broadcast ip, name and the rest of the stuff)
It also contains function to write out the wake on lan list
*/


// This will usually get called in the init functions to parse the wake on lan pc list
twol_list Read_PC_List()
{

	/*
	Todo:
	- Use the home directory for storing the lists
	- Update the config structure

	All this aplies to Write_PC_List() function (line 48)
	*/
	twol_list input_list;
	ini::IniFile ini_list;
	std::ostringstream list_path;
	list_path << homeDir << "/.spm/list.twol"; // The path to the list of computers

	ini_list.load(list_path.str());

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
	std::ostringstream list_path;
	list_path << homeDir << "/.spm/list.twol"; // Same as before

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

	out_list.save(list_path.str());
}
