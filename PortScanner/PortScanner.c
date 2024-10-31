#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int port_checker(const char *ip, int port){
  int check_sock;
  struct sockaddr_in server_address;
  struct timeval timeout;
  fd_set writefds;

  check_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (check_sock < 0){
    printf("Socket was not created successfully");
    return 0;
  }

  fcntl(check_sock, F_SETFL, O_NONBLOCK);

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  inet_pton(AF_INET, ip, &server_address.sin_addr);

  int connection = connect(check_sock, (struct sockaddr*) &server_address, sizeof(server_address));
  if(connection < 0 && errno != EINPROGRESS){
    close(check_sock);
    return 0;
  }

  FD_ZERO(&writefds);
  FD_SET(check_sock, &writefds);

  timeout.tv_sec = 2;
  timeout.tv_usec = 0;

  if (select(check_sock + 1, NULL, &writefds, NULL, &timeout) > 0){
    int so_error;
    socklen_t len = sizeof(so_error);
    getsockopt(check_sock, SOL_SOCKET, SO_ERROR, &so_error, &len);

    if (so_error == 0){
      close(check_sock);
      return 1; // port is open
      }
    }

  close(check_sock);
  return 0; // port is close

}

void scan_ports(const char *ip, int first_port, int last_port, char *buffer, size_t buffer_size){
  buffer[0] = '\0';

  for (int port = first_port; port <= last_port; port++){
    char port_scan_out[50];

    if(port_checker(ip, port) == 0){
      snprintf(port_scan_out, sizeof(port_scan_out), "Port: %d is closed\n", port);
    }
    else{
      snprintf(port_scan_out, sizeof(port_scan_out), "Port: %d is open\n", port);
    }

    if (strlen(buffer) + strlen(port_scan_out) < buffer_size){
      strcat(buffer, port_scan_out);
    }
    else{
      printf("Buffer size of exceeded");
      break;
    }
  }
}

