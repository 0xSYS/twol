

#ifdef __linux__
  #include <arpa/inet.h>
  #include <netinet/in.h>
  #include <sys/socket.h>
  #include <unistd.h>
#endif

#include <cstring>


#include "sckt_io.hpp"
#include "spm.hpp"
#include "dbg_log.hpp"
#include "config.hpp"






static SPMDebug dbg;
// static SPM spm;




void SPM_SocketIO::SndPowerAction(int actType, std::string target)
{
  /*
  Todo:
  Scan target and check what kind of target is passed (computer name automatic name or custom name / target IP)
  */
  int sckt = 0;
  struct sockaddr_in serv_addr;

  sckt = socket(AF_INET, SOCK_STREAM, 0);

  if(sckt < 0)
  {
    dbg.Log(SPMDebug::Err, "SndPowerAction", "Failed to create socket !!");
  }
  else
  {
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);


    if(inet_pton(AF_INET, target.c_str(), &serv_addr.sin_addr) <= 0)
    {
      dbg.Log(SPMDebug::Err, "SndPowerAction", "Invalid Address !!");
    }
    else
    {
      if(connect(sckt, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        dbg.Log(SPMDebug::Err, "SndPowerAction", "Failed to connect to ", target);
      }
      else
      {
        if(actType == 1)
        {
          send(sckt, "pwroff", strlen("pwroff"), 0);
        }
        else if(actType == 2)
        {
          send(sckt, "fpwroff", strlen("fpwroff"), 0);
        }
        else if(actType == 3)
        {
          send(sckt, "rbt", strlen("rbt"), 0);
        }
        else if(actType == 4)
        {
          send(sckt, "frbt", strlen("frbt"), 0);
        }
        close(sckt);
      }
    }
  }
}


void SPM_SocketIO::SndCustomSettings(std::string target, ServerSettings ss)
{
  int sckt = 0;
  std::ostringstream serialSettings; // Used for constructing the serialised server settings packet 

  struct sockaddr_in serv_addr;

  sckt = socket(AF_INET, SOCK_STREAM, 0);
  if(sckt < 0)
  {
    dbg.Log(SPMDebug::Err, "SndCustomSettings", "Failed to create socket !!");
  }
  else
  {

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);

    if (inet_pton(AF_INET, target.c_str(), &serv_addr.sin_addr) <= 0)
    {
      dbg.Log(SPMDebug::Err, "SndCustomSettings", "Invalid address / Adress not supported !!");
    }
    else
    {
      if (connect(sckt, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        dbg.Log(SPMDebug::Err, "SndCustomSettings", "Failed to connect to ", target);
      }
      else
      {
        // Constructing the settings packet
        serialSettings << "feedback="           << ss.feedback          << " allowSysInfo="  << ss.alowSysInfo;
        serialSettings << " dbgLog="            << ss.debugLog          << " port="          << ss.listenPort;
        serialSettings << " skipProcScan="      << ss.skipProcScan      << " stdoutCapture=" << ss.stdoutCapture;
        serialSettings << " terminateProceses=" << ss.terminateProceses << " writeLogFiles=" << ss.writeLogFiles;

        // Sending the packet to the desired target
        send(sckt, serialSettings.str().c_str(), strlen(serialSettings.str().c_str()), 0);
        close(sckt);
      }
    }
  }
}

void SPM_SocketIO::SndResetSettings(std::string target)
{
  int sckt = 0;
  struct sockaddr_in serv_addr;

  sckt = socket(AF_INET, SOCK_STREAM, 0);
  if(sckt < 0)
  {
    dbg.Log(SPMDebug::Err, "SndResetSettings", "Failed to create socket !!");
  }
  else
  {

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, target.c_str(), &serv_addr.sin_addr) <= 0)
    {
      dbg.Log(SPMDebug::Err, "SndResetSettings" , "Invalid address / Address not supported !!");
    }
    else
    {

      if (connect(sckt, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        dbg.Log(SPMDebug::Err, "SndResetSettings", "Failed to connect to ", target);
      }
      else
      {
        send(sckt, "RstSettings", strlen("RstSettings"), 0);
        // Todo: Get feddback check from server to spm client if this action executed successfully
        dbg.Log(SPMDebug::Success, "SndResetSettings", "Server settings reset");
        close(sckt);
      }
    }
  }
}


void SPM_SocketIO::SndClearLogs(std::string target)
{
  int sckt = 0;
  struct sockaddr_in serv_addr;

  sckt = socket(AF_INET, SOCK_STREAM, 0);
  if(sckt < 0)
  {
    dbg.Log(SPMDebug::Err, "SndClearLogs", "Failed to create socket !!");
  }
  else
  {

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);

    if(inet_pton(AF_INET, target.c_str(), &serv_addr.sin_addr) <= 0)
    {
      dbg.Log(SPMDebug::Err, "SndClearLogs", "Invalid address / Address not suported !!");
    }
    else
    {

      if(connect(sckt, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <= 0)
      {
        dbg.Log(SPMDebug::Err, "SndClearLogs", "Failed to connect to ", target);
      }
      else
      {
        send(sckt, "clrLogs", strlen("clrLogs"), 0);
        dbg.Log(SPMDebug::Success, "SndClearLogs", "Sent clear logs");
        close(sckt);
      }
    }
  }
}
