#pragma once

#include <string>
#include <vector>



// Global structure used for storing the app settings (io)
typedef struct
{
  bool pc_status_mpack;                 // Enable / disable pc status globally
  bool cli_mode;                        // Enable / disable cli arguments while tui is disabled
  bool debug_log;                       // Enable / disable debug log to file (logs are stored in /home/user/twol_logs)
  // Why did I made this -_-
  bool restrict_autolink;               // Enable linking the protected list files (linux only for now)
  bool restrict_mode;                   // Enable / disable restriction mode
  bool restrict_timeout;                // Enable / disable restrict mode timeout
  int rescrict_time_span;               // Set ammount of time a rescricted session can last (in minutes)
  std::string restr_list_path;          // Set custom path for the encrypted pc list
  int usr_index;                        // Maps all users that can run in restricted mode with a number (usr1, usr2)
  std::vector<std::string> restr_users; // Store all users that can enter restricted mode
} cfg;


void twol_cfg_write(cfg cfg_out);
cfg twol_cfg_read();
