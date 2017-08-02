#include "../include/adtpanel.h"

#define THETA QString(1,QChar(0x98,0x03))

AdtPanel::AdtPanel(QWidget *parent, Manager *manager, bool load_conf) : QWidget(parent), m_manager(manager)
{
    setGeometry(0, 0, 300, 500);
    setFixedSize(300, 300);

    m_lbl_lock = new QLabel("Lock panel:", this);
    m_lbl_lock->setGeometry(0, 0, 85, 20);

    m_combo_lock = new QComboBox(this);
    m_combo_lock->setGeometry(100, 0, 40, 20);
    m_combo_lock->addItem("0");
    m_combo_lock->addItem("1");

    m_lbl_avgm = new QLabel("Averaging mode:", this);
    m_lbl_avgm->setGeometry(0, 25, 120, 20);

    m_combo_avgm = new QComboBox(this);
    m_combo_avgm->setGeometry(130, 25, 85, 20);
    m_combo_avgm->addItem("None", "0");
    m_combo_avgm->addItem("Custom", "1");
    m_combo_avgm->addItem("Medium", "2");

    m_lbl_navg = new QLabel("# measurements (averaging):", this);
    m_lbl_navg->setGeometry(0, 50, 200, 20);

    m_edit_navg = new QLineEdit("[2;99]", this);
    m_edit_navg->setGeometry(210, 50, 50, 20);
    m_edit_navg->setEnabled(false);

    m_lbl_bias = new QLabel("Bias:", this);
    m_lbl_bias->setGeometry(0, 75, 50, 20);

    m_combo_bias = new QComboBox(this);
    m_combo_bias->setGeometry(70, 75, 85, 20);
    m_combo_bias->addItem("None", "0");
    m_combo_bias->addItem("Internal", "1");
    m_combo_bias->addItem("External", "2");

    m_lbl_vbia = new QLabel("DC preload voltage [0;5]:", this);
    m_lbl_vbia->setGeometry(0, 100, 170, 20);

    m_edit_vbia = new QLineEdit("V", this);
    m_edit_vbia->setGeometry(180, 100, 60, 20);
    m_edit_vbia->setEnabled(false);
    m_edit_vbia->setMaxLength(5);

    m_lbl_ibia = new QLabel("DC preload current [0.001;0.2]:", this);
    m_lbl_ibia->setGeometry(0, 125, 210, 20);

    m_edit_ibia = new QLineEdit("A", this);
    m_edit_ibia->setGeometry(220, 125, 60, 20);
    m_edit_ibia->setEnabled(false);
    m_edit_ibia->setMaxLength(6);

    m_lbl_volt = new QLabel("Measurement voltage [0.05;1.5]:", this);
    m_lbl_volt->setGeometry(0, 150, 220, 20);

    m_edit_volt = new QLineEdit("V", this);
    m_edit_volt->setGeometry(230, 150, 50, 20);
    m_edit_volt->setMaxLength(5);

    m_lbl_rate = new QLabel("Measurement speed:", this);
    m_lbl_rate->setGeometry(0, 175, 145, 20);

    m_combo_rate = new QComboBox(this);
    m_combo_rate->setGeometry(155, 175, 90, 20);
    m_combo_rate->addItem("Slow", "2");
    m_combo_rate->addItem("Medium", "1");
    m_combo_rate->addItem("Fast", "0");

    m_lbl_pmod = new QLabel("Measurement mode:", this);
    m_lbl_pmod->setGeometry(0, 200, 145, 20);

    m_combo_pmod = new QComboBox(this);
    m_combo_pmod->setGeometry(155, 200, 75, 20);
    m_combo_pmod->addItem("Auto", "0");
    m_combo_pmod->addItem("L-Q", "1");
    m_combo_pmod->addItem("L-R", "2");
    m_combo_pmod->addItem("C-D", "3");
    m_combo_pmod->addItem("C-R", "4");
    m_combo_pmod->addItem("R-Q", "5");
    m_combo_pmod->addItem("Z-"+THETA, "6");
    m_combo_pmod->addItem("Y+"+THETA, "7");
    m_combo_pmod->addItem("R+X", "8");
    m_combo_pmod->addItem("G+B", "9");
    m_combo_pmod->addItem("N+"+THETA, "10");
    m_combo_pmod->addItem("M", "11");

    m_lbl_outp = new QLabel("Display output mode:", this);
    m_lbl_outp->setGeometry(0, 225, 145, 20);

    m_combo_outp = new QComboBox(this);
    m_combo_outp->setGeometry(155, 225, 90, 20);
    m_combo_outp->addItem("Normal", "0");
    m_combo_outp->addItem("Relative", "1");
    m_combo_outp->addItem("Absolute", "2");

    connect(m_combo_lock, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_lock_changed(int)));
    connect(m_combo_avgm, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_avgm_changed(int)));
    connect(m_combo_bias, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_bias_changed(int)));
    connect(m_combo_rate, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_rate_changed(int)));
    connect(m_combo_pmod, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_pmod_changed(int)));
    connect(m_combo_outp, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_outp_changed(int)));
    connect(m_edit_navg, SIGNAL(textChanged(QString)), this, SLOT(handle_navg_changed(QString)));
    connect(m_edit_vbia, SIGNAL(textChanged(QString)), this, SLOT(handle_vbia_changed(QString)));
    connect(m_edit_ibia, SIGNAL(textChanged(QString)), this, SLOT(handle_ibia_changed(QString)));
    connect(m_edit_volt, SIGNAL(textChanged(QString)), this, SLOT(handle_volt_changed(QString)));

    if (load_conf) load_config();
    else {
        ask_hameg_settings();
        save_config();
    }

    this->show();
}

void AdtPanel::load_config() {
    if (NULL == m_manager) return;
    m_combo_lock->setCurrentText(m_manager->get_setting("LOCK"));
    m_combo_avgm->setCurrentIndex(m_manager->get_setting("AVGM").toInt());
    m_edit_navg->setText(m_manager->get_setting("NAVG"));
    m_combo_bias->setCurrentIndex(m_manager->get_setting("BIAS").toInt());
    m_edit_vbia->setText(m_manager->get_setting("VBIA"));
    m_edit_ibia->setText(m_manager->get_setting("IBIA"));
    m_edit_volt->setText(m_manager->get_setting("VOLT"));
    m_combo_rate->setCurrentText(m_manager->get_setting("RATE"));
    m_combo_pmod->setCurrentIndex(m_manager->get_setting("PMOD").toInt());
    m_combo_outp->setCurrentIndex(m_manager->get_setting("OUTP").toInt());
}

void AdtPanel::handle_lock_changed(int idx) {
    if (NULL != m_manager)
        m_manager->set_setting(tr("LOCK"), QString(1, QChar('0'+idx)));
}

void AdtPanel::handle_avgm_changed(int idx) {
    m_edit_navg->setEnabled(idx == 1);
    if (NULL != m_manager)
        m_manager->set_setting(tr("AVGM"), m_combo_avgm->currentData().toString());
}

void AdtPanel::handle_bias_changed(int idx) {
    if (NULL != m_manager)
        m_manager->set_setting(tr("BIAS"), m_combo_bias->currentData().toString());
    if (idx == 0) {
        m_edit_vbia->setEnabled(false);
        m_edit_ibia->setEnabled(false);
    } else {
        m_edit_vbia->setEnabled(true);
        m_edit_ibia->setEnabled(true);
    }
}

void AdtPanel::handle_rate_changed(int) {
    if (NULL != m_manager)
        m_manager->set_setting(tr("RATE"), m_combo_rate->currentData().toString());
}

void AdtPanel::handle_pmod_changed(int idx) {
    // Ok if PMOD is either of C-D, C-R, R-X, Z-O else HAMEG will return 'ERROR':
    m_edit_vbia->setEnabled((idx == 3) || (idx == 4) || (idx == 6) || (idx == 8));
    // Ok if PMOD is either of L-Q, L-R, N-O, M else HAMEG will return 'ERROR':
    m_edit_ibia->setEnabled((idx == 1) || (idx == 2) || (idx == 10) || (idx == 11));
    if (NULL != m_manager)
        m_manager->set_setting(tr("PMOD"), m_combo_pmod->currentData().toString());
}

void AdtPanel::handle_outp_changed(int) {
    if (NULL != m_manager)
        m_manager->set_setting(tr("OUTP"), m_combo_outp->currentData().toString());
}

void AdtPanel::ask_hameg_settings() {
    if (NULL == m_manager) return;

    if (m_manager->get_device_path().isEmpty()) \
        m_manager->set_device_path("/dev/serial/by-id/usb-HAMEG_Instruments_HO820_019641048-if00-port0");

    if (m_manager->get_fd() <= 0) {
        int fd = serial_init(\
                    m_manager->get_device_path().toStdString().c_str());

        if (fd <= 0) return;
        else m_manager->set_fd(fd);
    }

    QString avgm = m_manager->ask("AVGM?",1);
    m_combo_avgm->setCurrentIndex(m_combo_avgm->findData(avgm));

    if (avgm == "1") {
        m_edit_navg->setText(m_manager->ask("NAVG?",2));
        m_edit_navg->setEnabled(true);
    } else m_edit_navg->setEnabled(false);

    QString pmod = m_manager->ask("PMOD?",2);
    m_combo_pmod->setCurrentIndex(m_combo_pmod->findData(pmod));

    if (pmod == "3" || pmod == "4" || pmod == "6" || pmod == "8") {
        m_edit_vbia->setText(m_manager->ask("VBIA?",5));
        m_edit_vbia->setEnabled(true);
    } else m_edit_vbia->setEnabled(false);

    if (pmod == "1" || pmod == "2" || pmod == "10" || pmod == "11") {
        m_edit_ibia->setText(m_manager->ask("IBIA?",5));
        m_edit_ibia->setEnabled(true);
    } else m_edit_ibia->setEnabled(false);

    m_combo_bias->setCurrentIndex(m_combo_bias->findData(m_manager->ask("BIAS?",1)));
    m_combo_rate->setCurrentIndex(m_combo_rate->findData(m_manager->ask("RATE?",1)));
    m_combo_outp->setCurrentIndex(m_combo_outp->findData(m_manager->ask("OUTP?",1)));

    m_edit_volt->setText(m_manager->ask("VOLT?",4));
}

void AdtPanel::handle_navg_changed(QString) {
    if (NULL == m_manager) return;
    m_manager->set_setting("NAVG", m_edit_navg->text());
}

void AdtPanel::handle_vbia_changed(QString) {
    if (NULL == m_manager) return;
    m_manager->set_setting("VBIA", m_edit_vbia->text());
}

void AdtPanel::handle_ibia_changed(QString) {
    if (NULL == m_manager) return;
    m_manager->set_setting("IBIA", m_edit_ibia->text());
}

void AdtPanel::handle_volt_changed(QString txt) {
    if (NULL == m_manager) return;
    m_manager->set_setting("VOLT", txt);
}

void AdtPanel::save_config() {
    if (NULL == m_manager) return;
    m_manager->set_setting("LOCK", m_combo_lock->currentText());
    m_manager->set_setting("AVGM", m_combo_avgm->currentData().toString());
    m_manager->set_setting("NAVG", m_edit_navg->text());
    m_manager->set_setting("BIAS", m_combo_bias->currentData().toString());
    m_manager->set_setting("VBIA", m_edit_vbia->text());
    m_manager->set_setting("IBIA", m_edit_ibia->text());
    m_manager->set_setting("VOLT", m_edit_volt->text());
    m_manager->set_setting("RATE", m_combo_rate->currentData().toString());
    m_manager->set_setting("PMOD", m_combo_pmod->currentData().toString());
    m_manager->set_setting("OUTP", m_combo_outp->currentData().toString());
}
