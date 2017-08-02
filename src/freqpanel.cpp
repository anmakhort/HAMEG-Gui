#include "../include/freqpanel.h"

FreqPanel::FreqPanel(QWidget *parent, Manager *manager, bool _load_config_) : QWidget(parent), m_manager(manager)
{
    setGeometry(0, 0, 300, 300);
    setFixedSize(300, 300);

    m_lbl_freq = new QLabel("Base Frequency:", this);
    m_lbl_freq->setGeometry(0, 0, 110, 20);

    m_combo_freq = new QComboBox(this);
    m_combo_freq ->setGeometry(120, 0, 80, 20);

    m_checkboxes = new QVector<QCheckBox*>();

    const int n_cols = 4, n_rows = 18;
    int x_offs = 300/n_cols, y_offs = 240/n_rows;
    size_t i = 0;
    const size_t N = sizeof(FREQs)/sizeof(FREQs[0]);

    for (int row = 0; i < N && row < n_rows; row++) {
        for (int col = 0; i < N && col < n_cols; col++) {
            int _f_ = FREQs[i++];
            float f = (float)_f_;
            QString units = " Hz";
            if (f >= 1000) {
                f /= 1000.0f;
                units = " kHz";
            }
            QString freq = QString::number(f)+units;
            QString nbr_freq = QString::number(_f_);
            m_combo_freq->addItem(freq, nbr_freq);

            QCheckBox *cbox = new QCheckBox(freq, this);
            cbox->setObjectName(nbr_freq);
            cbox->setGeometry(col*x_offs, row*y_offs+20, 80, 20);
            m_checkboxes->push_back(cbox);
        }
    }

    if (_load_config_) load_config();
    else update_base_freq();

    m_btnDeselectAll = new QPushButton("Unselect All", this);
    m_btnDeselectAll->setGeometry(120, 255, 85, 20);

    m_btnSelectAll = new QPushButton("Select All", this);
    m_btnSelectAll->setGeometry(215, 255, 85, 20);

    connect(m_btnDeselectAll, SIGNAL(pressed()), this, SLOT(handle_unselect_all()));
    connect(m_btnSelectAll, SIGNAL(pressed()), this, SLOT(handle_select_all()));
    connect(m_combo_freq, SIGNAL(currentIndexChanged(int)), this, SLOT(handle_base_freq_changed(int)));

    if (m_manager) {
        connect(m_manager, SIGNAL(s_busy()), this, SLOT(handle_manager_busy()));
        connect(m_manager, SIGNAL(s_ok()), this, SLOT(handle_manager_ok()));
    }

    this->show();
}

FreqPanel::~FreqPanel() {
    if (NULL != m_checkboxes) delete m_checkboxes;
}

void FreqPanel::handle_manager_busy() {
    for (int i = 0; i < m_checkboxes->size(); i++)
        m_checkboxes->at(i)->setEnabled(false);
    m_combo_freq->setEnabled(false);
    m_btnDeselectAll->setEnabled(false);
    m_btnSelectAll->setEnabled(false);
}

void FreqPanel::handle_manager_ok() {
    for (int i = 0; i < m_checkboxes->size(); i++)
        m_checkboxes->at(i)->setEnabled(true);
    m_combo_freq->setEnabled(true);
    m_btnDeselectAll->setEnabled(true);
    m_btnSelectAll->setEnabled(true);
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

void FreqPanel::handle_base_freq_changed(int idx) {
    if (NULL == m_manager) return;
    m_manager->set_setting("FREQ", QString::number(FREQs[idx]));
}

QVector<QString>* FreqPanel::get_selected_freqs() {
    if (NULL == m_checkboxes) return NULL;
    QVector<QString> *ret = new QVector<QString>();
    for (int i = 0; i < m_checkboxes->size(); i++)
        if (m_checkboxes->at(i)->checkState() == Qt::Checked)
            ret->push_back(m_checkboxes->at(i)->objectName());
    return ret;
}

QString lst2str(const QVector<QString> * const lst, const QString separator) {
    if (NULL == lst || lst->size() == 0) return "";
    QString ret = "";
    for (auto it = lst->begin(); it != lst->end(); it++)
        ret += (*it) + separator;
    ret.resize(ret.size()-1); // remove last separator from the end
    return ret;
}

void FreqPanel::save_config() {
    if (NULL == m_manager) return;
    QVector<QString> *lst = get_selected_freqs();
    m_manager->set_setting("FSCAN", lst2str(lst, ";"));
    delete lst;
    m_manager->set_setting("FREQ", m_combo_freq->currentData().toString());
}

void FreqPanel::load_config() {
    if (NULL == m_manager) return;
    float freq = m_manager->get_setting("FREQ").toFloat();
    QString units = " Hz";
    if (freq >= 1000) {
        freq /= 1000.0f;
        units = " kHz";
    }
    m_combo_freq->setCurrentText(QString::number(freq)+units);

    QStringList lst = m_manager->get_setting("FSCAN").split(";");
    if (lst.isEmpty()) return;
    for (int i = 0; i < m_checkboxes->size() && i < lst.size(); i++) {
        if (m_checkboxes->at(i)->objectName() == lst.at(i))
            m_checkboxes->at(i)->setChecked(true);
    }
}

void FreqPanel::update_base_freq() {
    if (NULL == m_manager) return;

    float f = m_manager->ask("FREQ?",6).toFloat();
    QString units = " Hz";
    if (f >= 1000) {
        f /= 1000.0f;
        units = " kHz";
    }
    m_combo_freq->setCurrentText(QString::number(f)+units);
}
