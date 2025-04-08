#pragma once





enum LogTypes
{
  Info = 1,
  Success,
  Warn,
  Err
};


void Log(int logType, const char * fmt, ...);
