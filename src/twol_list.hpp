#pragma once



typedef struct twol_list
{
  std::string pcName;       // Optional
  std::string mac_addr;     // Required
  std::string broadcast_ip; // Required
	std::string pcIp;         // Optional
	int pc_count;             // Not for user!
};


twol_list Read_PC_List();
void Write_PC_List(twol_list out_pc_list);
