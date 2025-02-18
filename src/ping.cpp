#include "ping.hpp"

#include <iostream>
#include <oping.h>




// Send ping to a computer
// Use case: Check if the computer has booted the OS and connects to the internet
void spm_ping(const std::string& ip)
{
  // stuff
  pingobj_t *p;
  pingobj_iter_t *itr;

  std::cout << "RAW: " << ip << "\n";

  if(ip.empty())
  {
    std::cout << "IP String cannot be empty!\n";
  }
  
  const char * tempStr = ip.c_str();

  // Init ping object
  p = ping_construct();

  if(!p)
    std::cout << "Failed to initialize ping obj\n";

  if(ping_host_add(p, tempStr) != 0)
  {
    std::cout << "Failed to add host ping\n";
    ping_destroy(p);
  }

  if(ping_send(p) < 0)
  {
    std::cout << "Failed to send ping request\n";
    ping_destroy(p);
  }

  for(itr = ping_iterator_get(p); itr != nullptr; itr = ping_iterator_next(itr))
  {
    char *host = nullptr;
    double latency = 0.0;
    size_t host_sz = sizeof(host);
    size_t lat_sz = sizeof(latency);

    // ping_iterator_get_info(itr, PING_INFO_HOSTNAME, &host, &host_sz);
    // ping_iterator_get_info(itr, PING_INFO_LATENCY, &latency, &lat_sz);
    //
    // if (ping_iterator_get_info(itr, PING_INFO_HOSTNAME, &host, &host_sz) < 0 ||
    //         ping_iterator_get_info(itr, PING_INFO_LATENCY, &latency, &lat_sz) < 0) {
    //         std::cerr << "Error retrieving ping information.\n";
    //         continue;
    //     }
    //

    if (ping_iterator_get_info(itr, PING_INFO_ADDRESS, &host, &host_sz) == 0) {
    // std::cerr << "Failed to retrieve hostname.\n";
    std::cout << "Ping to " << host << " ";
} else {
    std::cout << "Ping failed!\n";
}



    // std::cout << "Ping to " << host << "| latency: " << latency << "\n"; 
  }

  ping_destroy(p);
}

