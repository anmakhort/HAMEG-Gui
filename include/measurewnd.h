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
#include <QFileDialog>

class MeasureWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MeasureWnd(QWidget *parent = 0);
    ~MeasureWnd();

    void closeEvent(QCloseEvent *event) override;

signals:
    void s_closing(QObject*);

public slots:
    void handle_btn_start();

private:
    QWidget *m_parent;
    QFile *m_file;
    QTextStream *m_stream;
};

#endif // MEASUREWND_H
