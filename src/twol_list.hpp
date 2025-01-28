#pragma once

#include <string>



// Global structure for 1 wake on lan pc
// This structure should be turned into an array so that more computers can be processed (io list as well as frontend list in the tui)
typedef struct twol_list
{
  std::string pcName;       // Optional
  std::string mac_addr;     // Required
  std::string broadcast_ip; // Required
	std::string pcIp;         // Optional
	int pc_count;             // Not for user!
};



// The function definitions
twol_list Read_PC_List();
void Write_PC_List(twol_list out_pc_list);
