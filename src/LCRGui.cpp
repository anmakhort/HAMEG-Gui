#include "../include/LCRGui.h"
#include "../include/serializer.h"
#include <QMessageBox>

#ifdef _DEBUG
#include <iostream>
#endif

LCRGui::LCRGui(QWidget *parent) : QMainWindow(parent), mdi_area(new QMdiArea) {
    setObjectName("LCRGui");

    createMenus();
    this->menuBar()->setNativeMenuBar(false);

    mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdi_area);

    //createSettingsWnd();
    //createConsoleWnd();
    //createMeasureWnd();

    setWindowTitle("HAMEG <LCR> Gui");
    setMinimumSize(300, 300);
    resize(650, 500);

    manager = new Manager();
}

LCRGui::~LCRGui() {
    delete manager;
}

void LCRGui::closeEvent(QCloseEvent *event) {
    if (mdi_area->subWindowList().size() > 0) mdi_area->closeAllSubWindows();
    event->accept();
}

void LCRGui::createMenus() {
    loadAct = new QAction(tr("Open config"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load a previously saved configuration"));
    connect(loadAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_loadConfig(bool)));

    saveAct = new QAction(tr("Save config"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save current configuration"));
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_saveConfig(bool)));

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcuts(QKeySequence::Close);
    exitAct->setStatusTip(tr("Close this application"));
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_exit(bool)));

    consoleViewAct = new QAction(tr("Console"), this);
    consoleViewAct->setStatusTip(tr("Show the console for direct serial communications"));
    connect(consoleViewAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_consoleView(bool)));

    measureViewAct = new QAction(tr("Measurement"), this);
    measureViewAct->setStatusTip(tr("Show the measurement window"));
    connect(measureViewAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_measureView(bool)));

    settingsAct = new QAction(tr("LCR Settings"), this);
    settingsAct->setStatusTip(tr("Open HAMEG LCR measurement settings"));
    connect(settingsAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_settings(bool)));

    aboutAct = new QAction(tr("About"), this);
    aboutAct->setStatusTip(tr("About this application"));
    connect(aboutAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_about(bool)));

    aboutQtAct = new QAction(tr("About Qt"), this);
    aboutQtAct->setStatusTip(tr("Load a previously saved configuration"));
    connect(aboutQtAct, SIGNAL(triggered(bool)), this, SLOT(handle_menu_aboutQt(bool)));

    fileMenu = this->menuBar()->addMenu(tr("File"));
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = this->menuBar()->addMenu(tr("View"));
    viewMenu->addAction(consoleViewAct);
    viewMenu->addAction(measureViewAct);

    settingsMenu = this->menuBar()->addMenu(tr("Settings"));
    settingsMenu->addAction(settingsAct);

    helpMenu = this->menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void LCRGui::handle_menu_loadConfig(bool) {
    QMap<QString,QString> *tmp = \
            Serializer::deserialize(\
                Serializer::datetime_path("./configurations"));
    if (NULL != tmp) {
        manager->update_all_settings(tmp);
        delete tmp;
    }
}

void LCRGui::handle_menu_saveConfig(bool) {
    Serializer::serialize(\
                manager->get_all_settings(), \
                Serializer::datetime_path("./configurations"));
}

void LCRGui::handle_menu_exit(bool) {
    //emit manager->s_exit();
    this->close();
}

void LCRGui::handle_menu_settings(bool) {
    QList<QMdiSubWindow*> lst = mdi_area->subWindowList();
    for (int i = 0; i < lst.size(); i++) {
        if (lst[i]->objectName() == "SettingsWnd") {
            return;
        }
    }
    createSettingsWnd();
}

void LCRGui::handle_menu_about(bool) {
    QMessageBox::about(this, "About", "LCRGui Application v1.0\n"
                                      "Autor: Anatolii Makhort\n"
                                      "Email: anmakhort@gmail.com");
}

void LCRGui::handle_menu_aboutQt(bool) {
    QMessageBox::aboutQt(this);
}

void LCRGui::handle_menu_consoleView(bool) {
    QList<QMdiSubWindow*> lst = mdi_area->subWindowList();
    for (int i = 0; i < lst.size(); i++) {
        if (lst[i]->objectName() == "SerialConsole") {
            return;
        }
    }
    createConsoleWnd();
}

void LCRGui::handle_menu_measureView(bool) {
    QList<QMdiSubWindow*> lst = mdi_area->subWindowList();
    for (int i = 0; i < lst.size(); i++) {
        if (lst[i]->objectName() == "MeasureWnd") {
            return;
        }
    }
    createMeasureWnd();
}

void LCRGui::createConsoleWnd() {
    SerialConsole *serialWnd = new SerialConsole(this);
    serialWnd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mdi_area->addSubWindow(serialWnd);
    mdi_area->subWindowList()[mdi_area->subWindowList().size()-1]->setObjectName(serialWnd->objectName());
    connect(serialWnd, SIGNAL(s_closing(QObject*)), this, SLOT(destroyActions(QObject*)));
    serialWnd->show();
}

void LCRGui::createMeasureWnd() {
    MeasureWnd *measureWnd = new MeasureWnd(this, manager);
    measureWnd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mdi_area->addSubWindow(measureWnd);
    mdi_area->subWindowList()[mdi_area->subWindowList().size()-1]->setObjectName(measureWnd->objectName());
    connect(measureWnd, SIGNAL(s_closing(QObject*)), this, SLOT(destroyActions(QObject*)));
    measureWnd->show();
}

void LCRGui::createSettingsWnd() {
    Settings *settingsWnd = new Settings(this, manager);
    settingsWnd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mdi_area->addSubWindow(settingsWnd);
    mdi_area->subWindowList()[mdi_area->subWindowList().size()-1]->setObjectName(settingsWnd->objectName());
    connect(settingsWnd, SIGNAL(s_closing(QObject*)), this, SLOT(destroyActions(QObject*)));
    settingsWnd->show();
}

void LCRGui::destroyActions(QObject *obj) {
    if (obj) {
#ifdef _DEBUG
        std::cout << "destroy:\t" << obj->objectName().toStdString() << "\t";
#endif
        QList<QMdiSubWindow*> lst = mdi_area->subWindowList();
        for (int i = 0; i < lst.size(); i++) {
            if (lst[i]->objectName() == obj->objectName()) {
#ifdef _DEBUG
                std::cout << i;
#endif
            }
        }
#ifdef _DEBUG
        std::cout << "\n";
#endif
    }
}
