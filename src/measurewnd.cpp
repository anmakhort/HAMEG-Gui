#include "../include/measurewnd.h"
#include "../include/rs232.h"

#include <iostream>

MeasureWnd::MeasureWnd(QWidget *parent, Manager *manager) : QWidget(parent), m_manager(manager) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("MeasureWnd");

    setGeometry(0,0,300,300);
    setFixedSize(300,300);
    setWindowTitle("LCR Measure");

    m_lbl_mode = new QLabel("Measurement mode:", this);
    m_lbl_mode->setGeometry(10, 10, 150, 20);

    m_combo_mode = new QComboBox(this);
    m_combo_mode->setGeometry(160, 10, 110, 20);
    m_combo_mode->addItem("LCR vs Time", "0");
    m_combo_mode->addItem("LCR vs Freq", "1");

    m_lbl_time = new QLabel("Total measurement time:", this);
    m_lbl_time->setGeometry(10, 40, 180, 20);

    m_edit_time = new QLineEdit("sec", this);
    m_edit_time->setGeometry(190, 40, 80, 20);
    m_edit_time->setEnabled(true);

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    timerID = m_timer->timerId();

    m_lbl_countdown = new QLabel("Time left:", this);
    m_lbl_countdown->setGeometry(10, 70, 150, 20);

    btn_start = new QPushButton("Run", this);
    btn_start->setGeometry(10, 100, 100, 100);
    btn_start->setEnabled(false);

    btn_stop = new QPushButton("Stop", this);
    btn_stop->setGeometry(180, 100, 100, 100);
    btn_stop->setEnabled(false);

    connect(m_combo_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_mode_changed(int)));
    connect(m_edit_time, SIGNAL(textChanged(QString)), this, SLOT(handle_time_changed(QString)));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(handle_timer()));
    connect(btn_start, SIGNAL(released()), this, SLOT(handle_btn_start()));
    connect(btn_stop, SIGNAL(released()), this, SLOT(handle_btn_stop()));
}

MeasureWnd::~MeasureWnd() {
    m_timer->stop();

    if (m_stream) {
        m_stream->flush();
        delete m_stream;
    }
    if (m_file) {
        m_file->close();
        delete m_file;
    }
}

void MeasureWnd::closeEvent(QCloseEvent *event) {
    emit s_closing(this);
    if (m_manager) emit m_manager->s_exit();
    event->accept();
}

void MeasureWnd::handle_mode_changed(int) {
    int mode = m_combo_mode->currentData().toInt();
    m_edit_time->setEnabled(0 == mode);
}

void MeasureWnd::handle_time_changed(QString time) {
    float t = time.toFloat();
    if (t > 0.f) {
        m_timer->setInterval((int)(t*1000));
        btn_start->setEnabled(true);
    } else btn_start->setEnabled(false);
}

void MeasureWnd::handle_timer() {
    btn_start->setEnabled(true);
    btn_stop->setEnabled(false);
}

void MeasureWnd::timerEvent(QTimerEvent *ev) {
    std::cout << "Event!\n";

    if (ev->timerId() == m_timer->timerId()) {
        m_lbl_countdown->setText("Time left: " + QString::number(m_timer->remainingTime()) + " sec");
    } else {
        QWidget::timerEvent(ev);
    }
}

void MeasureWnd::handle_btn_start() {
    if (m_manager) emit m_manager->s_meas_start();
    btn_start->setEnabled(false);
    btn_stop->setEnabled(true);

    if (m_file != NULL) return;

    QString name = tr("Select file to save measured data");
    QString save_path = QFileDialog::getSaveFileName(this, name, tr("/home/an"), tr("DATA (*.dat)"));
    if (!save_path.endsWith(".dat", Qt::CaseInsensitive)) save_path += ".dat";
    m_file = new QFile(save_path);
    if (!m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox(QMessageBox::Information, "Error", m_file->errorString());
        return;
    }
    m_stream = new QTextStream(m_file);
    *m_stream << "X,Y1,Y2\n";
    m_stream->flush();

    if (m_combo_mode->currentData().toInt() == 0) m_timer->start();
}

void MeasureWnd::handle_btn_stop() {
    if (m_manager) emit m_manager->s_meas_end();

    btn_start->setEnabled(true);
    btn_stop->setEnabled(false);

    if (m_stream != NULL) m_stream->flush();

    m_timer->stop();
}

void MeasureWnd::handle_manager_exit() {

}
