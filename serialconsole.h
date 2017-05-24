#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H

#include <QWidget>

class SerialConsole : public QWidget
{
    Q_OBJECT
public:
    explicit SerialConsole(QWidget *parent = 0);

signals:

public slots:
};

#endif // SERIALCONSOLE_H