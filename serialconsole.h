#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QCloseEvent>

class SerialConsole : public QWidget
{
    Q_OBJECT
public:
    explicit SerialConsole(QWidget *parent = 0);
    ~SerialConsole();

private:
    int _fd = -1;
    QLabel *m_lbl;
    QLineEdit *m_device;
    QLineEdit *m_command;
    QLineEdit *m_resp;
    QPushButton *m_btnConnect;
    QPushButton *m_btnSend;
    QPushButton *m_btnQuery;
    QPushButton *m_btnRead;
    QTextEdit *m_log;

    void closeEvent(QCloseEvent *event) override;

signals:
    void s_closing(QObject*);

private slots:
    void handle_btnConnect();
    void handle_btnSend();
    void handle_btnQuery();
    void handle_btnRead();

};

#endif // SERIALCONSOLE_H
