#pragma once





// Global structure used for storing the app settings (io)
typedef struct
{
  bool pc_status_mpack;
} cfg;


void twol_cfg_write(cfg cfg_out);
cfg twol_cfg_read();
