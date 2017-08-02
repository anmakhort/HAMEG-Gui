#ifndef MEASUREWND_H
#define MEASUREWND_H

#include <QObject>
#include <QWidget>
#include <QCloseEvent>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QTimer>
#include <QTimerEvent>

#include "manager.h"

class MeasureWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MeasureWnd(QWidget *parent = 0, Manager *manager = 0);
    ~MeasureWnd();

    void closeEvent(QCloseEvent *event) override;

signals:
    void s_closing(QObject*);

private slots:
    void handle_btn_start();
    void handle_btn_stop();
    void handle_manager_exit();
    void handle_timer();
    void handle_mode_changed(int);
    void handle_time_changed(QString);

    void timerEvent(QTimerEvent *event) override;

private:
    Manager *m_manager = NULL;
    QWidget *m_parent = NULL;

    QFile *m_file = NULL;
    QTextStream *m_stream = NULL;

    QLabel *m_lbl_mode = NULL;
    QComboBox *m_combo_mode = NULL;

    QLabel *m_lbl_time = NULL;
    QLineEdit *m_edit_time = NULL;

    int timerID = -1;
    QTimer *m_timer = NULL;
    QLabel *m_lbl_countdown = NULL;

    QPushButton *btn_start = NULL;
    QPushButton *btn_stop = NULL;
};

#endif // MEASUREWND_H
