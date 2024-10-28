#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    // Creating socket file descriptor
    // socket arg1: domain (IPv4 or IPv6), arg2: type (TCP or UDP), arg3: protocol (0 is a default TCP protocol)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    // setsockopt arg1: socket (created in previous if statement), arg2: level (SOL_SOCKET is socket level),
    // arg3: option name (rules of binding), arg4: opt value (ours is a point to a set value), arg5: option length
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // specifies that the socket will communicate with IPv4
    address.sin_family = AF_INET;
    // tells socket to listen on all available network interfaces
    address.sin_addr.s_addr = INADDR_ANY;
    // sets port number for socket
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    // bind arg 1: socket, arg2: refers to sockaddr struct info, arg3: address size
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    // listen arg1: socket, arg2: backlog
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    // accept arg1: socket, arg2: refers to sockaddr stuct info, arg3: address length
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  &addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer,
                   1024 - 1); // subtract 1 for the null
                              // terminator at the end
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    close(server_fd);
    return 0;
}
