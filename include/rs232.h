#ifndef RS232_H
#define RS232_H

#include <string>

#define BUFF_SIZE 256

int set_iface_attribs(int fd, int speed, int parity);
int set_blocking_mode(int fd, int block);

int serial_init(const char* device);
int serial_close(const int fd);

int serial_write(const int &fd, std::string message, const char *ending, int wait_us);
std::string serial_read(const int &fd);
std::string serial_query(const int &fd, std::string message, const char *ending, int resp_size);

#endif // RS232_H
