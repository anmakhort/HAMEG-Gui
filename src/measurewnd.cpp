#include "../include/measurewnd.h"

MeasureWnd::MeasureWnd(QWidget *parent, Manager *manager) : QWidget(parent), m_manager(manager) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("MeasureWnd");

    setGeometry(0,0,300,300);
    setFixedSize(300,300);
    setWindowTitle("LCR Measure");

    btn_start = new QPushButton("Run", this);
    btn_start->setGeometry(10,10,100,100);
    btn_start->show();

    btn_stop = new QPushButton("Stop", this);
    btn_stop->setGeometry(180,10,100,100);
    btn_stop->setEnabled(false);
    btn_stop->show();

    connect(btn_start, SIGNAL(released()), this, SLOT(handle_btn_start()));
    connect(btn_stop, SIGNAL(released()), this, SLOT(handle_btn_stop()));
}

MeasureWnd::~MeasureWnd() {
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
    //if (m_manager) emit m_manager->s_exit();
    event->accept();
}

void MeasureWnd::handle_btn_start() {
    //if (m_manager) emit m_manager->s_meas_start();
    btn_start->setEnabled(false);
    btn_stop->setEnabled(true);

    if (m_file != NULL) return;

    QString name = "Select file to save measured data";
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
}

void MeasureWnd::handle_btn_stop() {
    //if (m_manager) emit m_manager->s_meas_end();

    btn_start->setEnabled(true);
    btn_stop->setEnabled(false);

    if (m_stream != NULL) m_stream->flush();
}

void MeasureWnd::handle_manager_exit() {

}
