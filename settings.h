#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private:
    QVector<QLabel> *m_labels;
    QVector<QCheckBox> *m_checkboxes;
    QPushButton *m_btnSelectAll;
    QPushButton *m_btnDeselectAll;
    QPushButton *m_btnOK;

    void closeEvent(QCloseEvent *event) override;

signals:
    void s_closing(QObject*);

public slots:
};

#endif // SETTINGS_H
