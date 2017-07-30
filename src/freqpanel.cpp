#include "../include/freqpanel.h"

FreqPanel::FreqPanel(QWidget *parent) : QWidget(parent)
{
    setGeometry(0, 0, 200, 250);
    setFixedSize(200, 250);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::red);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    m_lblFreqs = new QLabel(this);
    m_lblFreqs->setText("Frequencies:");
    m_lblFreqs->setGeometry(75,10,100,10);
    m_lblFreqs->show();

    this->show();
}
