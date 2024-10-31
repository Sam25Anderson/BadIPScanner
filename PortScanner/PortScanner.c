#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

int port_checker(const char *ip, int port){
  int check_sock;
  struct sockaddr_in server_address;

  check_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (check_sock < 0){
    printf("Socket was not created successfully");
    return 0;
  }

  struct timeval timeout;
  timeout.tv_sec = 2;
  timeout.tv_usec = 0;
  setsockopt(check_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_address.sin_addr);

  int connection = connect(check_sock, (struct sockaddr*) &server_address, sizeof(server_address));
  close(check_sock);

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
}

void scan_ports(const char *ip, int first_port, int last_port, char *buffer, size_t buffer_size){
  for (int port = first_port; port <= last_port; port++){
    if(port_checker(ip, port) == 0){
      printf("Port: %d is closed\n", port);
    }
    else{
      printf("Port: %d is open\n", port);
    }
  }
}

