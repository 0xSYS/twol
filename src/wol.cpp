#include <string>
#include <cstdint>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#ifdef __WIN32
  #include <netdb.h>

  #define WIN32_LEAN_AND_MEAN
  #include <WinSock2.h>
  #include <WS2tcpip.h>
  #include <Windows.h>
  #pragma comment(lib, "Ws2_32.lib")
#endif

#ifdef _WIN32
  DWORD WINAPI recvdata(LPVOID);
  #define close closesocket
#else
  void* recvdata(void*);
#endif




#include "wol.hpp"
#include "dbg_log.hpp"
#include "globals.hpp"



// Parse and verify the mac addres

bool SPMWakeOnLan::parse_mac_addr(const std::string& mac, std::vector<uint8_t>& mac_bytes)
{
  mac_bytes.clear();

  std::istringstream iss(mac);
  std::string byte_str;

  while(std::getline(iss, byte_str, ':'))
  {
    if(byte_str.length() != 2 || !std::isxdigit(byte_str[0]) || !std::isxdigit(byte_str[1]))
    {
      return false;
    }

    try
    {
      mac_bytes.push_back(static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16)));
    }
    catch(const std::invalid_argument& e)
    {
      return false;
    }
    catch(const std::out_of_range& e)
    {
      return false;
    }    
  }
  return mac_bytes.size() == 6;
}

void SPMWakeOnLan::SndMagicPack(const std::string& mac_address, const std::string& broadcast_ip, int port)
{
  std::vector<uint8_t> mac_bytes;
  

  if(!parse_mac_addr(mac_address, mac_bytes))
  {
    dbg.Log(SPMDebug::Err, "Invalid MAC Address!!");
    return;
  }

  // Le Magik!

#ifdef __linux__ 
    std::vector<uint8_t> magic_packet;
#else
    std::vector<char> magic_packet;
#endif

  magic_packet.insert(magic_packet.end(), 6, 0xFF);

  for(int i = 0; i < 16; i++)
  {
    magic_packet.insert(magic_packet.end(), mac_bytes.begin(), mac_bytes.end());
  }

  int sockt = socket(AF_INET, SOCK_DGRAM, 0);

  if(sockt < 0)
  {
    dbg.Log(SPMDebug::Err, "Failed to create socket !");
    return;
  }


#ifdef __linux__
  int optval = 1;
#else
  const char* optval = "1";
#endif

  if(setsockopt(sockt, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0)
  {
    dbg.Log(SPMDebug::Err, "Failed to set socket options !");
    close(sockt);
    return;
  }

  struct sockaddr_in dest_addr;

  std::memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port);

  if(inet_pton(AF_INET, broadcast_ip.c_str(), &dest_addr.sin_addr) <= 0)
  {
    dbg.Log(SPMDebug::Err, "Invalid broadcast IP !");
    close(sockt);
#ifdef _WIN32
    WSACleanup();
#endif
    return;
  }

  ssize_t sent_bytes = sendto(sockt, magic_packet.data(), magic_packet.size(), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

  if(sent_bytes < 0)
  {
    dbg.Log(SPMDebug::Err, "Failed to send magick packet !!");
  }
  else
  {
    dbg.Log(SPMDebug::Success, "Magic pakcet sent to ", mac_address, "via ", broadcast_ip);
#ifdef _WIN32
    WSACleanup();
#endif
  }
  close(sockt); 
}
