#include "../include/freqpanel.h"

FreqPanel::FreqPanel(QWidget *parent, Manager *manager) : QWidget(parent), m_manager(manager)
{
    setGeometry(0, 0, 300, 275);
    setFixedSize(300, 275);

    m_checkboxes = new QVector<QCheckBox*>();

    const int n_cols = 4, n_rows = 18;
    int x_offs = 300/n_cols, y_offs = 240/n_rows;
    size_t i = 0;
    const size_t N = sizeof(FREQs)/sizeof(FREQs[0]);

    int checked_freq = (NULL != m_manager) ? \
                (m_manager->ask("FREQ?",6)).toInt() : 0;

    for (int row = 0; i < N && row < n_rows; row++) {
        for (int col = 0; i < N && col < n_cols; col++) {
            int _f_ = FREQs[i++];
            float f = (float)_f_;
            QString units = " Hz";
            if (f >= 1000) {
                f /= 1000.0f;
                units = " kHz";
            }
            QCheckBox *cbox = new QCheckBox(QString::number(f)+units, this);
            cbox->setObjectName(QString::number(_f_));
            cbox->setGeometry(col*x_offs, row*y_offs, 80, 20);
            cbox->setChecked(_f_ == checked_freq);
            m_checkboxes->push_back(cbox);
        }
    }

    m_btnDeselectAll = new QPushButton("Unselect All", this);
    m_btnDeselectAll->setGeometry(120, 235, 85, 20);

    m_btnSelectAll = new QPushButton("Select All", this);
    m_btnSelectAll->setGeometry(215, 235, 85, 20);

    connect(m_btnDeselectAll, SIGNAL(pressed()), this, SLOT(handle_unselect_all()));
    connect(m_btnSelectAll, SIGNAL(pressed()), this, SLOT(handle_select_all()));

    this->show();
}

FreqPanel::~FreqPanel() {
    if (NULL != m_checkboxes) delete m_checkboxes;
}

void FreqPanel::handle_select_all() {
    if (NULL == m_checkboxes) return;
    for (int i = 0; i < m_checkboxes->size(); i++)
        if (m_checkboxes->at(i)->checkState() == Qt::Unchecked)
            m_checkboxes->at(i)->setChecked(true);
}

void FreqPanel::handle_unselect_all() {
    if (NULL == m_checkboxes) return;
    for (int i = 0; i < m_checkboxes->size(); i++)
        if (m_checkboxes->at(i)->checkState() == Qt::Checked)
            m_checkboxes->at(i)->setChecked(false);
}

QVector<QString>* FreqPanel::get_selected_freqs() {
    if (NULL == m_checkboxes) return NULL;
    QVector<QString> *ret = new QVector<QString>();
    for (int i = 0; i < m_checkboxes->size(); i++)
        if (m_checkboxes->at(i)->checkState() == Qt::Checked)
            ret->push_back(m_checkboxes->at(i)->text());
    return ret;
}
