


#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>

#include <sys/stat.h>

#if defined(_WIN32) || defined(_WIN64)
  #include <Windows.h>
  #include <direct.h>
#endif



#include "utils.hpp"
#include "globals.hpp"
#include "dbg_log.hpp"





std::string SPMUtils::GetCurrentDate()
{
  std::ostringstream temp;
  auto cd = std::chrono::system_clock::now();
  std::time_t current_dt = std::chrono::system_clock::to_time_t(cd);
  std::tm local_tm =*std::localtime(&current_dt);
  temp << std::put_time(&local_tm, "%d.%m.%Y");
  return temp.str();
}


std::string SPMUtils::GetHomeDir()
{
#ifdef __linux
  return std::getenv("HOME");
#endif

#if defined (_WIN32) || defined (_WIN64)
  return std::getenv("USERPROFILE");
#endif 
}

void SPMUtils::makeDir(std::string d)
{
#ifdef __linux__
  if(mkdir(d.c_str(), 0777))
  {
    dbg.Log(SPMDebug::Err, "mkdir() failed !!");
  }
#endif

#if defined (_WIN32) || defined (_WIN64)
  if(CreateDirectory(d.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
  {
    dbg.Log(SPMDEbug::Err, "CreateDirectory() failed !! Err Code: " GetLastError());
  }
#endif
}

bool SPMUtils::checkDir(std::string d)
{
#ifdef __linux__
  struct stat s;

  if(stat(d.c_str(), &s) != 0)
    return false;
  else
    return true;
#endif

#if defined(_WIN32) || defined(_WIN64)
  DWORD attributes = GetFileAttributes(d.c_str());
  return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
#endif
}

 bool SPMUtils::checkFile(std::string f)
 {
#ifdef __linux__
  return access(f.c_str(), F_OK);
#endif

#if defined(_WIN32) || defined(_WIN64)
  DWORD fileAttr = GetFileAttributes(filename);
  return (fileAttr != INVALID_FILE_ATTRIBUTES && !(fileAttr & FILE_ATTRIBUTE_DIRECTORY));
#endif
 }
