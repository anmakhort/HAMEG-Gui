#include "../include/manager.h"

Manager::Manager() : QObject(NULL) {}

Manager::Manager(const Manager &manager) : QObject(NULL) {
    this->_fd = manager._fd;
    this->device_path = manager.device_path;
}

Manager::~Manager() {
    if (_fd > 0) serial_close(_fd);
    if (m_map_settings != NULL) delete m_map_settings;
}

void Manager::manage_fd() {
    if (_fd < 0) {
        if (NULL == device_path)
            device_path = DEFAULT_HAMEG_SYS_PATH;
        _fd = serial_init(device_path.toStdString().c_str());
    }
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

void Manager::update_all_settings(const QMap<QString,QString> * const map) {
    if (map == NULL || map->empty()) return;
    if (m_map_settings == NULL)
        m_map_settings = new QMap<QString,QString>();
    for (auto it = map->begin(); it != map->end(); it++) {
        (*m_map_settings)[it.key()] = it.value();
    }
}

QString Manager::ask(QString query, int sz) {
    manage_fd();
    QString ret = QString::fromStdString(\
                serial_query(_fd, query.toStdString(), "\r\n", sz));
    ret.resize(sz);
    return (ret.split('\r')[0]).split('\n')[0];
}
