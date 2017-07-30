#include "../include/manager.h"
#include <iostream>

Manager::Manager() {}

Manager::Manager(const Manager &manager) {
    this->_fd = manager._fd;
    this->device_path = manager.device_path;
}

Manager::~Manager() {
    if (_fd > 0) serial_close(_fd);
    if (m_map_settings != NULL) delete m_map_settings;
}

const QString Manager::get_setting(QString key) const {
    if (m_map_settings != NULL)
        return (*m_map_settings)[key];
    else return QString("");
}

void Manager::set_setting(const QString key, const QString value) {
    if (m_map_settings == NULL)
        m_map_settings = new QMap<QString,QString>();
    (*m_map_settings)[key] = value;
}
