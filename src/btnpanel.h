#ifndef BTNPANEL_H
#define BTNPANEL_H

#include <QObject>
#include <QWidget>

class BtnPanel : public QObject
{
    Q_OBJECT
public:
    explicit BtnPanel(QObject *parent = 0);

signals:

public slots:
};

#endif // BTNPANEL_H