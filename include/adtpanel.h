#ifndef ADTPANEL_H
#define ADTPANEL_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include "manager.h"

class AdtPanel : public QWidget
{
    Q_OBJECT
public:
    explicit AdtPanel(QWidget *parent = 0, Manager *manager = NULL);

signals:

private slots:
    void handle_lock_changed(int);
    void handle_avgm_changed(int);
    void handle_bias_changed(int);
    void handle_rate_changed(int);
    void handle_pmod_changed(int);
    void handle_outp_changed(int);

private:
    Manager *m_manager = NULL;

    QLabel *m_lbl_lock = NULL;
    QComboBox *m_combo_lock = NULL;

    QLabel *m_lbl_avgm = NULL;
    QComboBox *m_combo_avgm = NULL;

    QLabel *m_lbl_bias = NULL;
    QComboBox *m_combo_bias = NULL;

    QLabel *m_lbl_rate = NULL;
    QComboBox *m_combo_rate = NULL;

    QLabel *m_lbl_pmod = NULL;
    QComboBox *m_combo_pmod = NULL;

    QLabel *m_lbl_outp = NULL;
    QComboBox *m_combo_outp = NULL;

    QLabel *m_lbl_navg = NULL;
    QLineEdit *m_edit_navg = NULL;

    QLabel *m_lbl_vbia = NULL;
    QLineEdit *m_edit_vbia = NULL;

    QLabel *m_lbl_ibia = NULL;
    QLineEdit *m_edit_ibia = NULL;

    QLabel *m_lbl_volt = NULL;
    QLineEdit *m_edit_volt = NULL;

    void ask_hameg_settings();
};

#endif // ADTPANEL_H
