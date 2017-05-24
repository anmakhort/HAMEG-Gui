#ifndef MEASUREWND_H
#define MEASUREWND_H

#include <QWidget>
#include <QCloseEvent>

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
};

#endif // MEASUREWND_H
