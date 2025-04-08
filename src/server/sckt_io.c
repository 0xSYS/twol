#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>




#ifndef EXIT_FAILURE
  #define EXIT_FAILURE 1
#endif


#include "sckt_io.h"
#include "dbg.h"


void StartScktReception()
{
  int serv_fd, sckt;
  struct sockaddr_in addr;


  int opt = 1;
  int addrlen = sizeof(addr);
  char buffer[1024] = {0};

  // Create socket
  serv_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (serv_fd == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Attach socket to the port
  setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(DEFAULT_PORT);

  // Bind
  if (bind(serv_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen
  if (listen(serv_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // Accept a connection
  sckt = accept(serv_fd, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
  if (sckt < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // Read data
  read(sckt, buffer, 1024);
  Log(Info, "Recevied socket msg: %s\n", buffer);

  if(strcmp(buffer, "pwroff") == 0)
  {
    // Call Poweroff
  }
  else if(strcmp(buffer, "fpwroff") == 0)
  {
    // Force power off even when there's a process runing (Very dagerous)
  }
  else if(strcmp(buffer, "rbt") == 0)
  {
    // Call Reboot
  }
  else if(strcmp(buffer, "frbt") == 0)
  {
    // Force reboot even when there's a process runing (Still very dangerous)
  }

  // Close socket
  close(sckt);
  close(serv_fd);
}
