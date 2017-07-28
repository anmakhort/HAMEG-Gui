#include "../include/measurewnd.h"

MeasureWnd::MeasureWnd(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setObjectName("MeasureWnd");

    setGeometry(0,0,300,300);
    setFixedSize(300,300);
    setWindowTitle("LCR Measure");

    QPushButton *btn = new QPushButton("Run", this);
    btn->setGeometry(100,100,100,100);

    connect(btn, SIGNAL(released()), this, SLOT(handle_btn_start()));
}

MeasureWnd::~MeasureWnd() {
    m_stream->flush();
    m_file->close();
    delete m_file;
    delete m_stream;
}

void MeasureWnd::closeEvent(QCloseEvent *event) {
    emit s_closing(this);
    event->accept();
}

void MeasureWnd::handle_btn_start() {
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
