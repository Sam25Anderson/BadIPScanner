#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		printf("Please enter the server IP address"
		       " and range of ports to be scanned\n");
		printf("USAGE: %sd IPv4 First_Port Last_Port\n",
		       argv[0]);
		exit(1);
	}
	char tIP[16] = {0};
	strcpy(tIP, argv[1]); // Copy the IPv4 address
	char First_Port[6] = {0};
	strcpy(First_Port, argv[2]); // Copy the start_port
	char Last_Port[6] = {0};
	strcpy(Last_Port, argv[3]); // Copy the end_port

	// Start port-scanner
	port_scanner(tIP, First_Port, Last_Port);
	return 0;
}


struct addrinfo hints;
memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_INET;
hins.ai_socktype = SOCK_STREAM;

sockfd = socket(temp->ai_family, temp->ai_socktype,
		temp->ai_protocol);

if (sockfd < 0)
{
	printf("Port %d is NOT open.\n" port);
	continue;
}

status = connect(sockfd, temp->ai_addr,
		 temp->ai_addrlen);

if (status<0)
{
	printf("Port %d is NOT open.\n" port);
	close(sockfd);
	continue;
}

printf("Port %d is open.\n", port);
close(sockfd);


