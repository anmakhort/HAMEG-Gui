#include "../include/btnpanel.h"

BtnPanel::BtnPanel(QWidget *parent) : QWidget(parent)
{
    setGeometry(0, 0, 200, 50);
    setFixedSize(200, 50);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::green);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();
}
