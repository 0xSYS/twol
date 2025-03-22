#include "ping.hpp"

#include <chrono>
#include <ctime>
#include <iostream>

#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>





// Packet constants
#define PING_PKT_S 64
#define PORT_NO 0
#define PING_SLEEP_RATE 100000
#define RECV_TIMEOUT 1


int ping_loop = 1; // Ping once


struct ping_pkt
{
  struct icmphdr hdr;
  char msg[PING_PKT_S - sizeof(struct icmphdr)];
};


unsigned short checksum(void *b, int len)
{
  unsigned short *buf = b;
  unsigned int sum = 0;
  unsigned short result;

  for(sum = 0; len > 1; len -= 2)
  {
    sum += *buf++;
  }

  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  result = ~sum; // Never seen that before
}

void intHandler(int dummy)
{
  ping_loop = 0;
}


// DNS Lookup
char *dns_lookup(char *addr_host, struct sockaddr_in *addr_con)
{
  std::cout << "Resolving DNS...\n";
  struct hostent *host_entity;
  char *ip = (char *)malloc(NI_MAXHOST * sizeof(char));

  if((host_entity = gethostbyname(addr_host)) == NULL)
  {
    return NULL;
  }

  strcpy(ip, inet_ntoa(*(struct in_addr *) host_entity -> h_addr));
 (*addr_con).sin_family = host_entity -> h_addrtype;
 (*addr_con).sin_port = htons(PORT_NO);
 (*addr_con).sin_addr.s_addr = *(long *) host_entity -> h_addr;
  
  return ip;
}


char * reverse_dns_lookup(char *ip_addr)
{
  struct sockaddr_in temp_addr;
  socklen_t len;
  char buf[NI_MAXHOST], *ret_buf;

  temp_addr.sin_family = AF_INET;
  temp_addr.sin_addr.s_addr = inet_addr(ip_addr);
  len = sizeof(struct sockaddr_in);

  if(getnameinfo((struct sockaddr *) &temp_addr, len, buf, sizeof(buf), NULL, 0, NI_NAMEREQD))
  {
    std::cout << "Failed to reverse DNS lookup\n";
    return NULL;
  }

  ret_buf = (char *) malloc((strlen(buf) + 1) + sizeof(char));
  strcpy(ret_buf, buf);

  return ret_buf;
}


void send_ping(int ping_sockfd, struct sockaddr_in *ping_addr, char *ping_dom, char *ping_ip, char *rev_host)
{
  int ttl_val = 64;
  int msg_count = 0;
  int flag = 1;
  int msg_recevied_count = 0;
  int i;
  char rbuffer[128];
  struct ping_pkt pckt;
  struct timespec time_start, time_end, tfs, tfe;
  struct sockaddr_in r_addr;
   socklen_t addr_len;
  long double rtt_msec = 0;
  long double total_msec = 0;
  struct timeval tv_out;
  tv_out.tv_sec = RECV_TIMEOUT;
  tv_out.tv_usec = 0;

  clock_gettime(CLOCK_MONOTONIC, &tfs);

  if(setsockopt(ping_sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0)
  {
    std::cout << "Failed to set socket options!\n";
  }
  else
  {
    std::cout << "Socket set to TTL...\n";
  }

  setsockopt(ping_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv_out, sizeof tv_out);


  while(ping_loop)
  {
    flag = 1;

    bzero(&pckt, sizeof(pckt));
    pckt.hdr.type = ICMP_ECHO;
    pckt.hdr.un.echo.id = getpid();

    for(i = 0; i < sizeof(pckt.msg) - 1; i++)
    {
      pckt.msg[i] = i + '0';
    }

    pckt.msg[i] = 0;
    pckt.hdr.un.echo.sequence = msg_count++;
    pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));

    usleep(PING_SLEEP_RATE);

    clock_gettime(CLOCK_MONOTONIC, &time_start);
    if(sendto(ping_sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)ping_addr, sizeof(*ping_addr)) <= 0)
    {
      std::cout << "Failed to send packet!\n";
      flag = 0;
    }

    addr_len = sizeof(r_addr);
    if(recvfrom(ping_sockfd, rbuffer, sizeof(rbuffer), 0, (struct sockaddr *)&r_addr, &addr_len) <= 0 && msg_count > 1)
    {
      std::cout << "Failed to recieve packet\n";
    }
    else
    {
      clock_gettime(CLOCK_MONOTONIC, &time_end);

      double timeElapsed = ((double)(time_end.tv_nsec - time_start.tv_nsec)) / 1000000.0;
      rtt_msec = (time_end.tv_sec - time_start.tv_sec) * 1000.0 + timeElapsed;

      if(flag)
      {
        struct icmphdr *recv_hdr = (struct icmphdr *)rbuffer;
        if(!(recv_hdr -> type == 0 && recv_hdr -> code == 0))
        {
          std::cout << "Err: Packed recevied with ICMP type " << recv_hdr -> type << " code " << recv_hdr -> code << "\n";
        }
        else
        {
          std::cout << PING_PKT_S << " bytes from " << ping_dom << " (h: " << rev_host << ")" << "(ip: " << ping_ip << ")" << "msg_seq = " << msg_count << " ttl = " << ttl_val << " rtt = " << rtt_msec << "ms\n";
          msg_recevied_count++;
        }
      }
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &tfe);
  double timeElapsed = ((double)(tfe.tv_nsec - tfs.tv_nsec)) / 1000000.0;
  total_msec = (tfe.tv_sec - tfs.tv_sec) * 1000.0 + timeElapsed;

  std::cout << "==== [Ping Stat] ====\n";
  std::cout << msg_count << " packets sent, packets recevied: " << msg_recevied_count << " packet loss: " << ((msg_count - msg_recevied_count) / (double)msg_count) * 100.0 << " Total time: " << total_msec << "\n\n";
}
// Send ping to a computer
// Use case(Only for basic wake on lan suport): Check if the computer has booted the OS and connects to the internet
void spm_ping(const std::string& ip)
{
  // stuff
}

