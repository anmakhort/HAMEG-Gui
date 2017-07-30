#ifndef BTNPANEL_H
#define BTNPANEL_H

#include <QWidget>
#include <QPushButton>

class BtnPanel : public QWidget
{
    Q_OBJECT
public:
    explicit BtnPanel(QWidget *parent = 0);

signals:
    void s_btn_apply_pressed();
    void s_btn_reset_pressed();

public slots:

private:
    QPushButton *m_btnApply = NULL;
    QPushButton *m_btnFactoryReset = NULL;

};

#endif // BTNPANEL_H
