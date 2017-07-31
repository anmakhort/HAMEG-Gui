#ifndef BTNPANEL_H
#define BTNPANEL_H

#include <QWidget>
#include <QPushButton>
#include "manager.h"

class BtnPanel : public QWidget
{
    Q_OBJECT
public:
    explicit BtnPanel(QWidget *parent = 0, Manager *manager = NULL);

signals:
    void s_btn_apply_pressed();
    void s_btn_reset_pressed();

private slots:
    void handle_apply();
    void handle_reset();

private:
    Manager *m_manager = NULL;

    QPushButton *m_btnApply = NULL;
    QPushButton *m_btnFactoryReset = NULL;

};

#endif // BTNPANEL_H
