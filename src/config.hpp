#pragma once





// Global structure used for storing the app settings (io)
typedef struct
{
  bool pc_status_mpack;   // Enable / disable pc status globally
  bool cli_mode;          // Enable / disable cli arguments while tui is disabled
  bool debug_log;         // Enable / disable debug log to file (logs are stored in /home/user/twol_logs)
  bool restrict_autolink; // Enable linking the protected list files (linux only for now)
  bool restrict_mode;     // Enable / disable restriction mode
} cfg;


void twol_cfg_write(cfg cfg_out);
cfg twol_cfg_read();
