#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 10200

int main(int argc, char const* argv[]){
  int status, valread, client_fd;
  struct sockaddr_in address;
  char buffer[1024] = {0};

  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd < 0){
    printf("Sock was not created correctly");
    return 0;
  }

  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = inet_addr("127.0.0.1");

  int connection = connect(client_fd, (struct sockaddr*) &address, sizeof(address));
  if (connection < 0){
    printf("Connection was not created correctly");
    return 0;
  }

  valread = read(client_fd, buffer, 1024-1);
  printf("%s\n", buffer);

  close(client_fd);
  return 0;
}
