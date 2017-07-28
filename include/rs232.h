#ifndef RS232_H
#define RS232_H

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string>

#define BUFF_SIZE 256

int set_iface_attribs(int fd, int speed, int parity) {
    struct termios device;
    memset (&device, 0, sizeof device);
    if (tcgetattr (fd, &device) != 0) {
        std::cout << "error " << errno << " from tcgetattr\n";
        return -1;
    }

    cfsetospeed (&device, speed);
    cfsetispeed (&device, speed);

    device.c_cflag = (device.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    device.c_iflag &= ~IGNBRK;         // disable break processing
    device.c_lflag = 0;                // no signaling chars, no echo,
                                       // no canonical processing
    device.c_oflag = 0;                // no remapping, no delays
    device.c_cc[VMIN]  = 0;            // read doesn't block
    device.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    device.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
    device.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,

    device.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    device.c_cflag |= parity;
    device.c_cflag &= ~CSTOPB;
    device.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &device) != 0) {
        std::cout << "error " << errno << " from tcsetattr\n";
        return -1;
    }
    return 0;
}

int set_blocking_mode(int fd, int block=0) {
    struct termios device;
    memset (&device, 0, sizeof device);
    if (tcgetattr (fd, &device) != 0) {
        std::cout << "error " << errno << " from tggetattr\n";
        return -1;
    }
    device.c_cc[VMIN]  = block ? 1 : 0;
    device.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
    if (tcsetattr (fd, TCSANOW, &device) != 0) {
        std::cout << "error " << errno << " setting term attributes\n";
        return -1;
    }
    return 0;
}

int serial_init(const char* device) {
    int fd = open(device, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) return -1;
    if (set_iface_attribs(fd, B9600, 0) < 0) {
        std::cout << "Error setting attributes\n";
        return -1;
    }
    // Set non-blocking mode, this will protect us from
    // unauthorized readings (if there was no query prev):
    // in this case read(...) will return empty string.
    if (set_blocking_mode(fd, 0) < 0) {
        std::cout << "Error setting mode\n";
    }
    return fd;
}

int serial_close(const int &fd) {
    if (fd) return close(fd);
    else return -1;
}

int serial_write(const int &fd, std::string message, const char *ending, int wait_us = 0) {
    message.append(ending);
    int written = (int)write(fd, message.c_str(), (int)message.size());
    usleep(100*message.size() + wait_us);
    return written;
}

std::string serial_read(const int &fd) {
    char buff[BUFF_SIZE];
    // Need such type of reading because there was some problems
    // while reading responses from HAMEG LCR Meter, which seems to
    // cut strings (give partial responses) after each reading try.
    // This method will read ALL possible response.
    size_t offset = 0, n_read = 0;
    while ((n_read = read(fd, buff+offset, BUFF_SIZE-offset)) > 0) {
        offset += n_read;
        if (offset >= BUFF_SIZE) break;
    }
    if (offset == 0) return "";
    else return std::string(buff);
}

std::string serial_query(const int &fd, std::string message, const char *ending, int resp_size) {
    int status = serial_write(fd, message, ending, 100*resp_size);
    if (status > 0) return serial_read(fd);
    else return "";
}

#endif // RS232_H
