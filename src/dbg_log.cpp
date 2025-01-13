#include "err_list.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>







// Initialize log stuff before writing to the same log file
void log_init()
{
  // Do stuff here
  std::ofstream out_log_init("twol_log");
  time_t t_stamp_init;
  time(&t_stamp_init);
  out_log_init << "[ " << ctime(&t_stamp_init) << " ] - log_init().\n";
  out_log_init.close();
}

// Pretty simple tbh lol
int write_log(std::string s, int flags)
{
  std::ofstream out_log;
  time_t log_time_stamp;
  std::stringstream log_str;

  out_log.open("twol_log", std::ios::app);

  if(!out_log)
    return 1;
  else
  {
    // Do the rest
    time(&log_time_stamp);
    out_log << "[ " << ctime(&log_time_stamp) << " ] - " << s << "\n";
    out_log.close();
  }
  return 0;
}
