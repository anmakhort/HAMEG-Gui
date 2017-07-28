#include "../include/settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("SettingsWnd");

    setGeometry(300, 0, 300, 300);
    setFixedSize(300, 300);
    setWindowTitle("Measurement Settings");
}

Settings::~Settings() {

}

void Settings::closeEvent(QCloseEvent *event) {
    emit s_closing(this);
    event->accept();
}
