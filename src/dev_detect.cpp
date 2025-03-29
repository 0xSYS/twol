
#ifdef __linux__
  #include <ifaddrs.h>
  #include <arpa/inet.h>
  #include <netinet/in.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
  #include <winsock2.h>
  #include <iphlpapi.h>

  #pragma comment(lib, "iphlpapi.lib")
  #pragma comment(lib, "ws2_32.lib")
#endif
#include <string>
#include <vector>






#include "dev_detect.hpp"
#include "dbg_log.hpp"





std::vector<std::string> SPMDetect::CreateIP_Table()
{
  std::vector<std::string> ipTable;

#ifdef __linux__
  // dfgvdf
  struct ifaddrs *interfaces, *ifa;
  if (getifaddrs(&interfaces) == -1) {
      perror("getifaddrs");
      // return;
  }

  for (ifa = interfaces; ifa != nullptr; ifa = ifa->ifa_next) {
      if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) { // IPv4
          char ip[INET_ADDRSTRLEN];
          struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
          inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
          std::cout << ifa->ifa_name << " - " << ip << std::endl;
          // ipTable.push_back(ip);
      }
  }
  freeifaddrs(interfaces);
#endif
  
  return ipTable;
}
