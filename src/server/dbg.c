#include <stdio.h>
#include <stdarg.h>



#include "dbg.h"



void Log(int logType, const char * fmt, ...)
{
	va_list args;
  va_start(args, fmt);
  
  if(logType == 1)
  {
    printf("spm-serv: [\033[38;5;123mInfo\033[0m] -> ");
  }
  else if(logType == 2)
  {
    printf("spm-serv: [\033[38;5;41mSuccess\033[0m !] -> ");
  }
  else if(logType == 3)
  {
    printf("spm-serv: [\033[38;5;178mWarn\033[0m] -> ");
  }
  else if(logType == 4)
  {
    printf("spm-serv: [\033[38;5;196mErr\033[0m] -> ");
  }
  
  vprintf(fmt, args);

  puts("");
  
  va_end(args);
}
