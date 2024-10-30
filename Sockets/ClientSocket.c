#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 10100

int main(int argc, char const* argv[]){
  int status, valread, client_fd;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};

  client_fd = socket(AF_INET, SOCK_STREAM, 0);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  if (status < 0){
    perror("Connection failed");
    close(client_fd);
    return -1;
  }

  valread = read(client_fd, buffer, 1024-1);
  printf("%s\n", buffer);

  close(client_fd);
  return 0;
}
