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
/*
Create the log file and add a first line into it with the date and time and the function name log_init()
Then close it
*/





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
    // Get date and time and store it into a string
    time(&log_time_stamp);
    out_log << "[ " << ctime(&log_time_stamp) << " ] - " << s << "\n";
    out_log.close();
  }
  return 0;
}
/*
How it works ???
1) Opens the created log file (created once log_init() is called)
2) Checks if the file exists
3) If so create the string with date and time (which will also involve the use of the error list string array defined in err_list at line 9) that will be feed into the log file
4) Write and close the file

!!! Important Note !!!
Everytime when this function gets called it adds a new line 1 by 1 with all necessarry strings of the log

Todo:
- The log file names should have this naming pattern: twol_log_<hour> - <day> - <month> - <year>
Getting date and time helps specific error tracking.
*/
