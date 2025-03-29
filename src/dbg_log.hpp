#pragma once






#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

#ifdef __linux__
  #include <unistd.h>
  #include <sys/wait.h>
  #include <sys/types.h>
  #include <stdio.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
  #include <Windows.h>
#endif




inline void PrintArgs() {} // Base case for recursion

template <typename T, typename... Args>
inline void PrintArgs(T first, Args... rest)
{
  std::cout << first; // Print the first argument
  PrintArgs(rest...);        // Recurse for remaining arguments
}


inline void AppendToStream(std::ostringstream&) {}

template <typename T, typename... Args>
inline void AppendToStream(std::ostringstream& oss, T first, Args... rest)
{
    oss << first;
    AppendToStream(oss, rest...);
}


inline std::vector<std::string> parseCommand(const std::string& command) {
    std::vector<std::string> args;
    std::istringstream stream(command);
    std::string arg;
    bool inQuotes = false;
    std::string temp;

    while (stream) {
        char c = stream.get();
        if (stream.eof()) break;

        if (c == '"' || c == '\'') {  // Handle both single and double quotes
            inQuotes = !inQuotes;
        } else if (c == ' ' && !inQuotes) {  // Space outside quotes
            if (!temp.empty()) {
                args.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }

    if (!temp.empty()) args.push_back(temp);
    return args;
}


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
      std::cout << "libspm: [\033[38;5;123mInfo\033[0m] -> " << mainStr;
    }
    else if(logType == 2)
    {
      std::cout << "libspm: [\033[38;5;41mSuccess\033[0m !] - > " << mainStr;
    }
    else if(logType == 3)
    {
      std::cout << "libspm: [\033[38;5;178mWarn\033[0m] -> " << mainStr;
    }
    else if(logType == 4)
    {
      std::cerr << "libspm: [\033[38;5;196mErr\033[0m] -> " << mainStr;
    }
    else if(logType == 0)
    {
      std::cout << "libspm: [ - ] -> " << mainStr;
    }
    // Forgor to print the rest of the args XD
    
    PrintArgs(r...); // Process remaining arguments
    std::cout << std::endl;
  }
  template<typename T, typename... Args >
  inline void MsgBoxLog(int logType, T mainStr, Args... r)
  {
    // safasf
    std::ostringstream text;

    text << mainStr;

    
    AppendToStream(text, r...);

// For security reasons there's a lot of code below
// !!! PLS DO NOT EVER TOUCH THIS !!!
// 🡇 🡇 🡇
#ifdef __linux__
    std::ostringstream cmd;
    pid_t p = fork();
    if(logType == 1)
    {
      cmd << "zenity --info --title='Server Power Management - Information' --text='" << text.str() << "'";
    }
    else if(logType == 2)
    {
      cmd << "zenity --info --title='Server Power Management - Success' --text='" << text.str() << "'";
    }
    else if(logType == 3)
    {
      cmd << "zenity --warning --title='Server Power Management - Warning' --text='" << text.str() << "'";
    }
    else if(logType == 4)
    {
      cmd << "zenity --error --title='Server Power Management - Error' --text='" << text.str() << "'";
    }


    std::string command = cmd.str();
    std::vector<std::string> args = parseCommand(command);

    std::vector<char*> c_args;
    for (auto& s : args) {
        c_args.push_back(s.data());  // Convert std::string to char*
    }
    c_args.push_back(nullptr);  // Null-terminate

    if(p == 0)
    {
      execvp(c_args[0], c_args.data());
      perror("execlp failed");
      _exit(1);
    }
    else if(p > 0)
    {
      int stat;
      waitpid(p, &stat, 0);
    }
    else
    {
      perror("fork failed");
    }
#endif
// 🡅 🡅 🡅
// !!! DO NOT EVER TOUCH THIS !!!

#if defined(_WIN32) || defined(_WIN64)
    int msgBoxID;
    std::string cppStr = text.str();
    std::wstring wstr(cppStr.begin(), cppStr.end());
    LPCWSTR temp = wstr.c_str();


    if(logType == 1)
    {
      msgBoxID = MessageBoxW(NULL, (LPCWSTR)temp, (LPCWSTR)L"Server Power Management - Info", MB_ICONINFORMATION | MB_OK);
    }
    else if(logType == 2)
    {
      msgBoxID = MessageBoxW(NULL, (LPCWSTR)temp, (LPCWSTR)L"Server Power Management - Sucess", MB_ICONINFORMATION | MB_OK);
    }
    else if(logType == 3)
    {
      msgBoxID = MessageBoxW(NULL, (LPCWSTR)temp, (LPCWSTR)L"Server Power Management - Warning", MB_ICONEXCLAMATION | MB_OK);
    }
    else if(logType == 4)
    {
      msgBoxID = MessageBoxW(NULL, (LPCWSTR)temp, (LPCWSTR)L"Server Power Management - Error", MB_ICONERROR | MB_OK);
    }
#endif
  }
};
