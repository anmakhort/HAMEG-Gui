#include "../include/settings.h"
#include "../include/serializer.h"
#include <QGridLayout>

Settings::Settings(QWidget *parent, Manager *manager, bool load_config) : QWidget(parent), m_manager(manager) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("SettingsWnd");

    setGeometry(300, 0, 630, 325);
    setFixedSize(630, 325);
    setWindowTitle("Measurement Settings");

    if (manager->get_fd() < 0) {
        QMap<QString,QString> *tmp = Serializer::deserialize("./default.conf");
        if (NULL != tmp) {
            manager->update_all_settings(tmp);
            delete tmp;
            load_config = true;
        }
    }

    m_freqpanel = new FreqPanel(this, manager, load_config);
    m_btnpanel = new BtnPanel(this, manager);
    m_adtpanel = new AdtPanel(this, manager, load_config);

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
    m_freqpanel->update_base_freq();
    m_adtpanel->ask_hameg_settings();
}

void Settings::handle_save_config(bool) {
    if (NULL != m_adtpanel) m_adtpanel->save_config();
    if (NULL != m_freqpanel) m_freqpanel->save_config();
    emit s_saved(true);
}
