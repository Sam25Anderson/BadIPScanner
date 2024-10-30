#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define TIMEOUT 1;

int port_checker(const char *ip, int port){
  int check_sock;
  struct sockaddr_in server_address;

  check_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (check_sock < 1){
    printf("Socket was not created successfully");
    return 0;
  }

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_address.sin_addr);

  int  connection = connect(check_sock, (struct sockaddr*) &server_address, sizeof(server_address));
  if (connection < 0){
    // port is closed
    close(check_sock);
    return 0;
    }
  else{
    // port is open
    close(check_sock);
    return 1;
  }
  close(check_sock);
  return 0;
}

void scan_ports(const char *ip, int first_port, int last_port){
  for (int port = first_port; port <= last_port; port++){
    if(port_checker(ip, port) == 0){
      printf("Port: %d is closed", port);
    }
    else{
      printf("Port: %d is open", port);
    }
  }



}

