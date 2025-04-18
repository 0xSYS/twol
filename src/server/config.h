#pragma once


#include <stdbool.h>




typedef struct
{
  bool allow_sys_info;
  bool dbg_log;
  bool write_log_file;
  bool skip_proc_scan;
  bool terminate_processes;
  bool stdout_capture;
  bool feedback;
  int port;
}configuration;

void ReadConfig();
void WriteConfig(configuration cfg);
