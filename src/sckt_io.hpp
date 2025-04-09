#pragma once




#include <string>
#include <vector>



#define DEFAULT_PORT 8080


class SPM_SocketIO
{
  public:
  /*
  System information structure
  */
  typedef struct
  {
    std::string usrName;
    std::string ip;
    std::string broadcastIP;
    std::string macAddr;
    std::string batteryInfo;
  }sysInfo;

  typedef struct
  {
    bool feedback;                 // Enable / disable feedback after sending a packet
    bool skipProcScan;             // Enable / disable scanning the current process list before executing a power action
    bool debugLog;                 // Enable / disable general debuging (This also includes sending minimal debug information from server to frontend)
    bool writeLogFiles;            // Enable / disable writing to log files
    bool alowSysInfo;              // Enable / disable sending system information trough the socket
    std::string terminateProceses; // Values: Never, Always, Always first
    int listenPort;                // Use different port for sending / recepting the packets
  }ServerSettings;
  
  enum ActionTypes
  {
    Poweroff = 1,
    ForcePoweroff, // The forced power actions should be avoided from being used as they can cause system corruptions if not handeled carefully
    Reboot,
    ForceReboot
  };
  
    void SndPowerAction(int actType, std::string target);    // Send power action to a device (Poweroff / reboot)
    sysInfo GetSysInfo();                                    // Retrieve system information of a specific device
    std::vector <sysInfo> GetSysInfoArr(std::string target); // Retrieve system information from multiple devices into an aray
    void SetCustomProcBlaclist(std::string ProcName);        // Add specific process to the black list (When executing power action it checks if the process and prevents reboot or poweroff if runing)
    void SndCustomSettings(ServerSettings);                  // Send custom configuration for the server via sockets
    void SndResetSettings(std::string target);               // Reset server to default settings
    void SndClearLogs(std::string target);                   // Send clearance of the log files
    void SndStopServer(std::string target);                  // Stops the server from listening
    void SndResumeServer(std::string target);                // Resume the server
    void SndKillServer(std::string target);                  // Kill the server process
};
