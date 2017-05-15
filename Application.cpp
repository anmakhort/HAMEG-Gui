#include <QApplication>
#include <iostream>
#include "lcrmeasure.h"
#include "serial_communication.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    LCRMeasure lcr;
    lcr.show();

    int fd = open("/dev/serial/by-id/usb-HAMEG_Instruments_HO820_019641048-if00-port0", O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        std::cout << "Error opening device\n";
        return -1;
    }
    if (set_iface_attribs(fd, B9600, 0) < 0) {
        std::cout << "Error setting attributes\n";
        return -1;
    }
    if (set_blocking_mode(fd, 1) < 0) {
        std::cout << "Error setting mode\n";
    }

    std::cout << (int)write(fd, "*IDN?\r", 6) << "\n";
    usleep(100 * (50+ 7));

    char buff[200];
    std::cout << (int)read(fd, buff, 100) << "\n";
    std::cout << buff << "\n";

    close(fd);

    return app.exec();
}
