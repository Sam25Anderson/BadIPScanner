#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 10100

void test_function(char *buffer, size_t size){
  int offset = 0;
  for (int i = 1; i < 10; i++){
    offset += snprintf(buffer + offset, size - offset, "%d\n", i);
    if (offset >= size){
      break;
    }
  }
}

int main(int argc, char const* argv[]){
  int server_fd, new_socket;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  int opt = 1;
  char buffer[1024] = {0};

  test_function(buffer, sizeof(buffer));

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
  return 0;
}








