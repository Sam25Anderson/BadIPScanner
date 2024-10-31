#ifndef PortScanner_H
#define PortScanner_H

int port_checker(const char *ip, int port);
void scan_ports(const char *ip, int first_port, int last_port, char *buffer, size_t buffer_size);

#endif
