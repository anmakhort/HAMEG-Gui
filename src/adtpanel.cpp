#include "adtpanel.h"

AdtPanel::AdtPanel(QWidget *parent) : QWidget(parent)
{
    setGeometry(0, 0, 100, 280);
    setFixedSize(100, 280);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::blue);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();
}

void AdtPanel::handle_btn_apply_pressed() {

}
