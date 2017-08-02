#include "../include/btnpanel.h"
#include "../include/rs232.h"

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
    if (NULL == m_manager) return;

    const QMap<QString,QString> *cfg = m_manager->get_all_settings();

    if (NULL == cfg || cfg->size() == 0) return;

    emit m_manager->s_busy();

    for (auto it = cfg->begin(); it != cfg->end(); it++) {
        if (it.key() != "FSCAN") {
            serial_write(m_manager->get_fd(), it.key().toStdString()+it.value().toStdString(), "\r\n", 500);
        }
    }

    emit m_manager->s_ok();
    emit s_btn_apply_pressed();
}

void BtnPanel::handle_reset() {
    if (NULL == m_manager) return;
    serial_write(m_manager->get_fd(), "*RST", "\r\n", 0);
    emit s_btn_reset_pressed();
}
