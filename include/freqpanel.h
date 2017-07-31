#ifndef FREQPANEL_H
#define FREQPANEL_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include "manager.h"


static const unsigned int FREQs[] = {   20, 24, 25, 30, 36, 40, 45, 50, 60, 72, 75, 80,
                                        90, 100, 120, 150, 180, 200, 240, 250, 300, 360, 400, 450,
                                        500, 600, 720, 750, 800, 900, 1000, 1200, 1500, 1800, 2000, 2400,
                                        2500, 3000, 3600, 4000, 4500, 5000, 6000, 7200, 7500, 8000, 9000, 10000,
                                        12000, 15000, 18000, 20000, 24000, 25000, 30000, 36000, 40000, 45000, 50000, 60000,
                                        72000, 75000, 80000, 90000, 100000, 120000, 150000, 180000, 200000  };

class FreqPanel : public QWidget
{
    Q_OBJECT
public:
    explicit FreqPanel(QWidget *parent = 0, Manager *manager = NULL);
    ~FreqPanel();

    QVector<QString>* get_selected_freqs();

signals:

private slots:
    void handle_select_all();
    void handle_unselect_all();

private:
    Manager *m_manager = NULL;

    QVector<QCheckBox*> *m_checkboxes = NULL;
    QPushButton *m_btnSelectAll = NULL;
    QPushButton *m_btnDeselectAll = NULL;
};

#endif // FREQPANEL_H
