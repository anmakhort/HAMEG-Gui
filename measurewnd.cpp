#include "measurewnd.h"
#include <QPushButton>

MeasureWnd::MeasureWnd(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("MeasureWnd");

    setGeometry(0,0,300,300);
    setFixedSize(300,300);
    setWindowTitle("LCR Measure");

    QPushButton *btn = new QPushButton("TEST", this);
    btn->setGeometry(100,100,100,100);
}

MeasureWnd::~MeasureWnd() {

}

void MeasureWnd::closeEvent(QCloseEvent *event) {
    emit s_closing(this);
    event->accept();
}
