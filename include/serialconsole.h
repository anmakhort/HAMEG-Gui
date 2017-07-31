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

    QLabel *m_lbl = NULL;
    QLineEdit *m_device = NULL;
    QLineEdit *m_command = NULL;
    QLineEdit *m_resp = NULL;
    QPushButton *m_btnConnect = NULL;
    QPushButton *m_btnSend = NULL;
    QPushButton *m_btnQuery = NULL;
    QPushButton *m_btnRead = NULL;
    QTextEdit *m_log = NULL;

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
