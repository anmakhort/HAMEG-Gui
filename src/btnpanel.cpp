#include "../include/btnpanel.h"

BtnPanel::BtnPanel(QWidget *parent, Manager *manager) : QWidget(parent), m_manager(manager)
{
    setGeometry(0, 0, 200, 25);
    setFixedSize(300, 25);

    m_btnApply = new QPushButton("Apply", this);
    m_btnApply->setGeometry(200, 5, 80, 20);

    m_btnFactoryReset = new QPushButton("Factory Reset", this);
    m_btnFactoryReset->setGeometry(80, 5, 100, 20);

    connect(m_btnApply, SIGNAL(released()), this, SLOT(handle_apply()));
    connect(m_btnFactoryReset, SIGNAL(released()), this, SLOT(handle_reset()));

    this->show();
}

void BtnPanel::handle_apply() {
    emit s_btn_apply_pressed();
}

void BtnPanel::handle_reset() {
    emit s_btn_reset_pressed();
}
