#ifndef FREQPANEL_H
#define FREQPANEL_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

class FreqPanel : public QWidget
{
    Q_OBJECT
public:
    explicit FreqPanel(QWidget *parent = 0);

    QVector<QString> get_selected_freqs();

signals:

public slots:

private:
    QLabel *m_lblFreqs = NULL;
    QVector<QCheckBox> *m_checkboxes = NULL;
    QPushButton *m_btnSelectAll = NULL;
    QPushButton *m_btnDeselectAll = NULL;

};

#endif // FREQPANEL_H
