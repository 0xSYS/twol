

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
    dbg.Log(SPMDebug::Err, "Failed to create socket");
  }
  else
  {
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);


    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
      dbg.Log(SPMDebug::Err, "Invalid Address !");
    }
    else
    {
      if(connect(sckt, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        dbg.Log(SPMDebug::Err, "Connection failed");
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
