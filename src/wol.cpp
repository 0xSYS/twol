#include <string>
#include <cstdint>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>

#ifdef __linux__
 #include <arpa/inet.h>
 #include <sys/socket.h>
 #include <unistd.h>
 #include <netdb.h>
#endif


#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #define _WINSOCK_DEPRECATED_NO_WARNINGS
  #include <windows.h>
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #pragma comment(lib, "Ws2_32.lib")
#endif

#ifdef _WIN32
  DWORD WINAPI recvdata(LPVOID);
  #define close closesocket      // Used to resemble the linux close socket function on windows


  
#else
  void* recvdata(void*);
#endif




#include "wol.hpp"
#include "dbg_log.hpp"
// #include "globals.hpp"






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

// This is where the Wake on LAN takes place
void SPMWakeOnLan::SndMagicPack(const std::string& mac_address, const std::string& broadcast_ip, int port)
{
  std::vector<uint8_t> mac_bytes;
  SPMDebug dbg;
  
  // Verify the MAC addres
  if(!parse_mac_addr(mac_address, mac_bytes))
  {
    dbg.Log(SPMDebug::Err, "Invalid MAC Address!!");
    return;
  }
  else
  {
#if defined(_WIN32) || defined(_WIN64)
    // Construct the magic packet
    std::vector<uint8_t> magic_packet(6, 0xFF);
    for (int i = 0; i < 16; i++)
    {
        magic_packet.insert(magic_packet.end(), mac_bytes.begin(), mac_bytes.end());
    }

    // Initialize Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        dbg.Log(SPMDebug::Err, "Failed to initialize Winsock!");
        return;
    }

    SOCKET sockt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockt == INVALID_SOCKET) {
        dbg.Log(SPMDebug::Err, "Failed to create socket !");
        WSACleanup();
        return;
    }

    int optval = 1;
    if (setsockopt(sockt, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(optval)) == SOCKET_ERROR) {
        dbg.Log(SPMDebug::Err, "Failed to set socket options !");
        closesocket(sockt);
        WSACleanup();
        return;
    }

    sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, broadcast_ip.c_str(), &dest_addr.sin_addr) != 1) {
        dbg.Log(SPMDebug::Err, "Invalid broadcast IP !");
        closesocket(sockt);
        WSACleanup();
        return;
    }

    int sent_bytes = sendto(sockt, (char*)magic_packet.data(), magic_packet.size(), 0,
                            (struct sockaddr*)&dest_addr, sizeof(dest_addr));

    if (sent_bytes == SOCKET_ERROR) {
        dbg.Log(SPMDebug::Err, "Failed to send magic packet !");
    } else {
#ifdef ANSI_ESCAPES
        dbg.Log(SPMDebug::Success, "Magic packet successfully sent to \033[38;5;94m", mac_address, "\033[0m via \033[38;5;94m", broadcast_ip, "\033[0m");
#else
        dbg.Log(SPMDebug::Success, "Magic packet sent successfully to ", mac_address, " via ", broadcast_ip);
#endif        
    }

    closesocket(sockt);
    WSACleanup();
#endif

#ifdef __linux__
    std::vector<uint8_t> magic_packet;

    magic_packet.insert(magic_packet.end(), 6, 0xFF);

    for(int i = 0; i < 16; i++)
    {
      magic_packet.insert(magic_packet.end(), mac_bytes.begin(), mac_bytes.end());
    }

    int sockt = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockt < 0)
    {
      std::cout << "Failed to create socket!\n";
      dbg.Log(SPMDebug::Err, "Failed to create socket !");
      return;
    }

    int optval = 1;
    if(setsockopt(sockt, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0)
    {
      dbg.Log(SPMDebug::Err, "Failed to set socket options !");
      return;
    }

    struct sockaddr_in dest_addr;

    std::memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, broadcast_ip.c_str(), &dest_addr.sin_addr) <= 0)
    {
      dbg.Log(SPMDebug::Err, "Invalid broadcast address !");
      close(sockt);
      return;
    }

    ssize_t sent_bytes = sendto(sockt, magic_packet.data(), magic_packet.size(), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

    if(sent_bytes < 0)
    {
      dbg.Log(SPMDebug::Err, "Failes to send magic pakcet !");
    }
    else
    {
#ifdef ANSI_ESCAPES
      dbg.Log(SPMDebug::Success, "Magic packet send successfully to \033[38;5;94m", mac_address, "\033[0m via \033[38;5;94m", broadcast_ip, "\033[0m");
#else
      dbg.Log(SPMDebug::Success, "Magic packet successfully sent to ", mac_address, " via ", broadcast_ip);
#endif            
    }
    close(sockt);
#endif
  }
}
