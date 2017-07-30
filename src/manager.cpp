#include "../include/manager.h"

Manager::Manager() {}

Manager::Manager(const Manager &manager) {
    this->_fd = manager._fd;
    this->device_path = manager.device_path;
}

Manager::~Manager() {
    if (_fd > 0) serial_close(_fd);
}
