#ifndef ADTPANEL_H
#define ADTPANEL_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>

class AdtPanel : public QWidget
{
    Q_OBJECT
public:
    explicit AdtPanel(QWidget *parent = 0);

signals:

public slots:
    void handle_btn_apply_pressed();

private:
    QComboBox *m_combo_lock = NULL;
    QComboBox *m_combo_avgm = NULL;
    QComboBox *m_combo_bias = NULL;
    QComboBox *m_combo_rate = NULL;
    QComboBox *m_combo_pmod = NULL;
    QComboBox *m_combo_outp = NULL;

    QLineEdit *m_edit_navg = NULL;
    QLineEdit *m_edit_vbia = NULL;
    QLineEdit *m_edit_ibia = NULL;
    QLineEdit *m_edit_volt = NULL;
};

#endif // ADTPANEL_H
