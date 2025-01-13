#include <cstdint>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>





bool parse_mac_addr(const std::string& mac, std::vector<uint8_t>& mac_bytes)
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



void send_magic_pack(const std::string& mac_address, const std::string& broadcast_ip, int port = 9)
{
  std::vector<uint8_t> mac_bytes;

  if(!parse_mac_addr(mac_address, mac_bytes))
  {
    std::cout << "Invalid MAC Addres!!\n";
    return;
  }

  // Le Magik!

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
    return;
  }

  int optval = 1;
  if(setsockopt(sockt, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0)
  {
    std::cout << "Failed to set socket options!!!\n";
    return;
  }

  struct sockaddr_in dest_addr;

  std::memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port);

  if(inet_pton(AF_INET, broadcast_ip.c_str(), &dest_addr.sin_addr) <= 0)
  {
    std::cout << "Invalid brodcast IP address!\n";
    close(sockt);
    return;
  }

  ssize_t sent_bytes = sendto(sockt, magic_packet.data(), magic_packet.size(), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

  if(sent_bytes < 0)
  {
    std::cout << "Failed to send magic packet!\n";
  }
  else
  {
    std::cout << "Magic packet sent successfully to " << mac_address << " via " << broadcast_ip << "\n";
  }
  close(sockt);
}
