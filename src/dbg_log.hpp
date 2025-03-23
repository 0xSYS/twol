#pragma once






#include <iostream>





class SPMDebug
{
  public:
  enum logTypes
  {
    Info = 1,
    Success,
    Warn,
    Err,
    noType = 0
  };


  template <typename T, typename... Args>
  inline void Log(int logType, T mainStr, Args... r)
  {
    if(logType == 1)
    {
      std::cout << "libspm: [\033[38;5;123mInfo\033[0m] -> " << mainStr << "\n";
    }
    else if(logType == 2)
    {
      std::cout << "libspm: [\033[38;5;41mSuccess\033[0m !] - > " << mainStr << "\n";
    }
    else if(logType == 3)
    {
      std::cout << "libspm: [\033[38;5;178mWarn\033[0m] -> " << mainStr << "\n";
    }
    else if(logType == 4)
    {
      std::cout << "libspm: [\033[38;5;196mErr\033[0m] -> " << mainStr << "\n";
    }
    else if(logType == 0)
    {
      std::cout << "libspm: [ - ] -> " << mainStr << "\n";
    }
  }
};
