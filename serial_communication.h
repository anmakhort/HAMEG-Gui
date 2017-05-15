#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H


#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>


int set_iface_attribs(int fd, int speed, int parity) {
    struct termios device;
    memset (&device, 0, sizeof device);
    if (tcgetattr (fd, &device) != 0) {
        //error_message ("error %d from tcgetattr", errno);
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
        //error_message ("error %d from tcsetattr", errno);
        return -1;
    }
    return 0;
}

int set_blocking_mode(int fd, int block=0) {
    struct termios device;
    memset (&device, 0, sizeof device);
    if (tcgetattr (fd, &device) != 0) {
        //error_message ("error %d from tggetattr", errno);
        return -1;
    }

    device.c_cc[VMIN]  = block ? 1 : 0;
    device.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &device) != 0)
        //error_message ("error %d setting term attributes", errno);
        return -1;
    return 0;
}


#endif // SERIAL_COMMUNICATION_H
