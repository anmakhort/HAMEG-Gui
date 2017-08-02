#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QString>
#include <QMap>
#include "rs232.h"

class Manager : public QObject
{
    Q_OBJECT

public:
    Manager();
    Manager(const Manager&);
    ~Manager();

    int get_fd() { return _fd; }
    void set_fd(const int fd) { _fd = fd; }

    const QString get_device_path() const { return device_path; }
    void set_device_path(const QString path) { device_path = path; }

    const QString get_setting(QString key) const;
    void set_setting(const QString key, const QString value);

    const QMap<QString,QString>* get_all_settings() const { return m_map_settings; }
    void update_all_settings(const QMap<QString,QString> * const map);

    QString ask(QString query, int sz);

signals:
    void s_meas_start();
    void s_meas_end();
    void s_exit();
    void s_busy();
    void s_ok();

private:
    int _fd = -1;
    QString device_path;
    QMap<QString, QString> *m_map_settings = NULL;

};

#endif // MANAGER_H
