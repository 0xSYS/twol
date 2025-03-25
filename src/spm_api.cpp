

#include <vector>
#include <string>
#include <cstdint>



#include "spm.hpp"
#include "api_utils.h"
#include "wol.hpp"

SPMWakeOnLan wol_exp;
SPM spm_exp;






extern "C"
{
  void API_EXPORT SPM_Iit()
  {
    spm_exp.Init();
  }

  const char * API_EXPORT SPM_GetVersion()
  {
    return "Version 1.0.0";
  }

  void API_EXPORT SPM_SafeExit()
  {
    spm_exp.Terminate();
  }

  void API_EXPORT SPM_Set(unsigned int setting, void * val, unsigned int cbVal)
  {
    // efesdfesdf
  }
  
  bool API_EXPORT SPM_VerifyMAC_Address(const char * m, const uint8_t * m_bytes)
  {
    std::string strConv(m);
    std::vector<uint8_t> mac_bytesConv;
    mac_bytesConv.assign(m_bytes, m_bytes + sizeof(m_bytes) / sizeof(m_bytes[0]));
    return wol_exp.parse_mac_addr(strConv, mac_bytesConv);
  }

  void API_EXPORT SPM_WakeOnLAN(const char * mac_addr, const char * broadcast_ip, int port)
  {
    std::string mac_addr_strConv(mac_addr);
    std::string br_ip_strConv(broadcast_ip);
    wol_exp.SndMagicPack(mac_addr_strConv, br_ip_strConv, port);
  }

  void API_EXPORT SPM_AddPC(const char * name, const char * mac_addr, const char * broadcast_ip, const char * ip, bool restricted)
  {
    // Todo...
  }

  void API_EXPORT SPM_RmPC(const std::string name)
  {
    // Todo...
  }

  void API_EXPORT SPM_SndCustomCheck(const char * default_ip)
  {
    // Todo...
  }

  void API_EXPORT SPM_GetCustomList(const char * path)
  {
    // Todo...
    // Should return the structure as an array of computers / servers
  }

  void API_EXPORT SPM_RemoveCustomList(const char * path)
  {
    // Todo...
  }

  void API_EXPORT SPM_Detect()
  {
    // Todo...
    // Should retur an array containing the structure of computers / servers
    // Parameters to return:
    // - IP, MAC Address, Broadcast IP, user(s) 
  }  
}
