#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include "PortChecker.h"

#define PORT 10200

int main(int argc, char const* argv[]){
  int server_fd, new_socket;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  int opt = 1;
  char buffer[4096] = {0};

  memset(buffer, 0, sizeof(buffer));

  scan_ports("127.0.0.1", 1500, 1510, buffer, sizeof(buffer));

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = INADDR_ANY;

  bind(server_fd, (struct sockaddr*)&address, sizeof(address));

  listen(server_fd, 3);

  new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);

  send(new_socket, buffer, strlen(buffer), 0);

  close(new_socket);
  close(server_fd);

  printf("%s\n", buffer); // to test what the buffer holds

  return 0;
}








