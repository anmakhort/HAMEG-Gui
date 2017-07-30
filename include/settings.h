#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>
#include <QComboBox>
#include <QLineEdit>

#include "manager.h"

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0, Manager *manager = 0);
    ~Settings();

private:
    Manager *m_manager = NULL;

    QPushButton *m_btnApply = NULL;
    QPushButton *m_btnFactoryReset = NULL;

    QLabel *m_lblFreqs = NULL;
    QVector<QCheckBox> *m_checkboxes = NULL;
    QPushButton *m_btnSelectAll = NULL;
    QPushButton *m_btnDeselectAll = NULL;

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

    void closeEvent(QCloseEvent *event) override;

signals:
    void s_closing(QObject*);

public slots:
};

#endif // SETTINGS_H
