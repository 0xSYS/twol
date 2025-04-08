

#include <vector>
#include <string>
#include <cstdint>



#include "spm.hpp"
#include "api_utils.h"
#include "wol.hpp"
#include "dev_detect.hpp"

SPMWakeOnLan wol_exp;
SPM spm_exp;
SPMDetect spm_detct;






API_EXPORT void SPM_Init()
{
  spm_exp.Init();
}

API_EXPORT void SPM_SafeExit()
{
  spm_exp.Terminate();
}

API_EXPORT bool SPM_ParseMac(std::string mac, std::vector<uint8_t> &mac_bytes)
{
  return wol_exp.parse_mac_addr(mac, mac_bytes);
}

API_EXPORT void SPM_SndMagicPacket(std::string mac_addr, std::string broadcastIP, int port = 9)
{
  wol_exp.SndMagicPack(mac_addr, broadcastIP, port);
}

API_EXPORT std::vector<std::string> SPM_DeviceDetect()
{
  return spm_detct.CreateIP_Table();
}

API_EXPORT void SPM_Snd_Reboot(int mode, std::string ip)
{
  // Call c++
}

API_EXPORT void SPM_SndPowerOff(int mode, std::string ip)
{
  // Call c++
}
