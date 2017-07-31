#include "../include/settings.h"
#include <QGridLayout>

Settings::Settings(QWidget *parent, Manager *manager) : QWidget(parent), m_manager(manager) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("SettingsWnd");

    setGeometry(300, 0, 630, 300);
    setFixedSize(630, 300);
    setWindowTitle("Measurement Settings");

    m_freqpanel = new FreqPanel(this, manager);
    m_btnpanel = new BtnPanel(this, manager);
    m_adtpanel = new AdtPanel(this, manager);

    QGridLayout *layout = new QGridLayout();
    this->setLayout(layout);

    layout->addWidget(m_adtpanel, 0, 0, -1, 1);
    layout->addWidget(m_freqpanel, 0, 1, 1, 1);
    layout->addWidget(m_btnpanel, 1, 1, 1, 1);

    connect(m_btnpanel, SIGNAL(s_btn_apply_pressed()), this, SLOT(handle_apply_pressed()));
    connect(m_btnpanel, SIGNAL(s_btn_reset_pressed()), this, SLOT(handle_reset_pressed()));
}

Settings::~Settings() {
}

void Settings::closeEvent(QCloseEvent *event) {
    emit s_closing(this);
    event->accept();
}

void Settings::handle_apply_pressed() {
    \
}

void Settings::handle_reset_pressed() {
    \
}
