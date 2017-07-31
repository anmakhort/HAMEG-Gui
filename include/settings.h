#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QComboBox>
#include <QLineEdit>

#include "manager.h"
#include "freqpanel.h"
#include "btnpanel.h"
#include "adtpanel.h"

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0, Manager *manager = 0);
    ~Settings();

private:
    Manager *m_manager = NULL;

    FreqPanel *m_freqpanel = NULL;
    BtnPanel *m_btnpanel = NULL;
    AdtPanel *m_adtpanel = NULL;

    void closeEvent(QCloseEvent *event) override;

signals:
    void s_closing(QObject*);

private slots:
    void handle_apply_pressed();
    void handle_reset_pressed();

};

#endif // SETTINGS_H
