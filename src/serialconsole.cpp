#include "../include/serialconsole.h"
#include "../include/rs232.h"

SerialConsole::SerialConsole(QWidget *parent, Manager *manager) : QWidget(parent), m_manager(manager) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("SerialConsole");

    setGeometry(0, 0, 300, 300);
    setFixedSize(300, 300);
    setWindowTitle("Serial Console");

    m_lbl = new QLabel("Device: ", this);
    m_lbl->setGeometry(10, 10, 50, 30);

    m_device = new QLineEdit("/dev/serial/by-id/usb-HAMEG_Instruments_HO820_019641048-if00-port0", this);
    m_device->setGeometry(65, 10, 150, 30);

    m_command = new QLineEdit(this);
    m_command->setGeometry(10, 50, 150, 30);
    m_command->setPlaceholderText("Type here the command to send");

    m_resp = new QLineEdit(this);
    m_resp->setGeometry(10, 85, 150, 30);
    m_resp->setPlaceholderText("Here will be the response from the device");

    m_btnConnect = new QPushButton("Connect", this);
    m_btnConnect->setGeometry(220, 10, 70, 30);

    m_btnSend = new QPushButton("Send", this);
    m_btnSend->setGeometry(165, 50, 60, 30);
    m_btnSend->setEnabled(false);

    m_btnQuery = new QPushButton("Query", this);
    m_btnQuery->setGeometry(230, 50, 60, 30);
    m_btnQuery->setEnabled(false);

    m_btnRead = new QPushButton("Read", this);
    m_btnRead->setGeometry(165, 85, 125, 30);
    m_btnRead->setEnabled(false);

    m_log = new QTextEdit(this);
    m_log->setGeometry(10, 120, 280, 170);
    m_log->setAcceptRichText(false);
    m_log->setReadOnly(true);
    m_log->setEnabled(true);

    connect(m_btnConnect, SIGNAL(released()), this, SLOT(handle_btnConnect()));
    connect(m_btnSend, SIGNAL(released()), this, SLOT(handle_btnSend()));
    connect(m_btnQuery, SIGNAL(released()), this, SLOT(handle_btnQuery()));
    connect(m_btnRead, SIGNAL(released()), this, SLOT(handle_btnRead()));
}

SerialConsole::~SerialConsole() {
}

void SerialConsole::closeEvent(QCloseEvent *event) {
    emit s_closing(this);
    event->accept();
}

void SerialConsole::handle_btnConnect() {
    QString dev = m_device->text();

    if (m_manager->get_device_path() != dev) {
        m_log->append("Closing old connection to device: " + m_manager->get_device_path() + \
                      "and opening for: " + dev);
        serial_close(m_manager->get_fd());
        m_manager->set_fd(-1);
        m_manager->set_device_path(dev);
    }

    if (m_manager->get_fd() <= 0) {
        int fd = serial_init(dev.toStdString().c_str());
        m_manager->set_fd(fd);
    }

    if (m_manager->get_fd() < 0) {
        m_log->append("Error opening device!");
    } else {
        m_btnConnect->setEnabled(false);
        m_btnSend->setEnabled(true);
        m_btnQuery->setEnabled(true);
        m_btnRead->setEnabled(true);
        m_log->setEnabled(true);
        m_log->append("Connection established!");
    }
}

void SerialConsole::handle_btnSend() {
    m_log->append("Sending <" + m_command->text() + \
                  tr("> : ") + \
                  (serial_write(m_manager->get_fd(), m_command->text().toStdString(), \
                                "\r", 5000) == 0 ? "FALSE" : "TRUE"));
}

void SerialConsole::handle_btnRead() {
    m_log->append("Read: " + QString::fromStdString(serial_read(m_manager->get_fd())));
}

void SerialConsole::handle_btnQuery() {
    m_log->append("Query <" + m_command->text() + "> : " + \
                  QString::fromStdString(\
                      serial_query(m_manager->get_fd(), \
                                   m_command->text().toStdString(), "\r", 256)));
}
