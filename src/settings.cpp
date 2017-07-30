#include "../include/settings.h"
#include <QGridLayout>

Settings::Settings(QWidget *parent, Manager *manager) : QWidget(parent), m_manager(manager) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("SettingsWnd");

    setGeometry(300, 0, 300, 300);
    setFixedSize(300, 300);
    setWindowTitle("Measurement Settings");

    m_freqpanel = new FreqPanel(this);
    m_btnpanel = new BtnPanel(this);
    m_adtpanel = new AdtPanel(this);

    QGridLayout *layout = new QGridLayout();
    this->setLayout(layout);

    layout->addWidget(m_adtpanel, 0, 0, -1, 1);
    layout->addWidget(m_freqpanel, 0, 1, 1, 1);
    layout->addWidget(m_btnpanel, 1, 1, 1, 1);

    m_manager->set_setting(tr("PMOD"), tr("0"));

    /*
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(m_freqpanel);
    vlayout->addWidget(m_btnpanel);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(m_adtpanel);
    hlayout->addLayout(vlayout);
    */
}

Settings::~Settings() {
}

void Settings::closeEvent(QCloseEvent *event) {
    emit s_closing(this);
    event->accept();
}
