#pragma once




#include <string>
#include <vector>



#define DEFAULT_PORT 8080


class SPM_SocketIO
{
  public:
  typedef struct
  {
    std::string usrName;
    std::string ip;
    std::string broadcastIP;
    std::string macAddr;
    std::string batteryInfo;
  }sysInfo;
  
  enum ActionTypes
  {
    Poweroff = 1,
    ForcePoweroff,
    Reboot,
    ForceReboot
  };
  
    /*void SndReboot(int mode, std::string target);
    void SndPoweroff(int mode, std::string target);
    void SndCustomAction(int mode, std::string target);
    // This dosen't make sense
    */
    void SndPowerAction(int actType, std::string target);
    sysInfo GetSysInfo();
    std::vector <sysInfo> GetSysInfoArr();
    void SetCustomProcBlaclist(std::string ProcName);
};
