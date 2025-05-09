#pragma once


#include <string>



// All possible errors and warnings to be used for loging into file and into the tui status bar
inline std::string spm_msg_stat[27] =
{
	"Magick Packet parse error!\n",
	"Wake On Lan failed!\n",
	"Failed to save configuration!\n",
	"Invalid MAC address entered!\n",
	"Invalid MAC address found in pc list!\n",
  "Failed to load 'pc_list.twol' !\n",
  "Failed to save 'pc_list.twol' !\n",
  "Invalid broadcast IP\n",
  "Failed to parse broadcast IP\n",
  "Missing broadcast IP from 'pc_list.twol' at ",
  "Missing MAC address from 'pc_list.twol' at ",
  "Invalid broadcast IP found in 'pc_list.twol' at ",
  "Failed to check for power status!\n",
  "Invalid IP entered!\n",
  "Invalid IP found in 'pc_list.twol' !\n",
  "Failed to send magick packet!\n",
  "No status response from ",
  "Failed to write log file!\n",
  "Writing to log file failed!\n",
  "Failed to get home user directory!\n",
  "Failed to create 'twol' directory in '.config'!\n",
  "Invalid configuration!\n",
  "No configuration found\n",
  "No pc list found\n",
  "Timeout disabeld!!\n",
  "Restrict mode timeout!!\n",
  "Failed to send SPM packet!\n"
};

// int log_init_stat;


// To be implemented...


void log_init();
int write_log(std::string s, int flags);
