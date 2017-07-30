#ifndef LCRMEASURE_H
#define LCRMEASURE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMdiArea>
#include <QCloseEvent>
#include <QMdiSubWindow>

#include "serialconsole.h"
#include "measurewnd.h"
#include "settings.h"
#include "manager.h"

class LCRGui : public QMainWindow
{
    Q_OBJECT
public:
    explicit LCRGui(QWidget *parent = 0);
    ~LCRGui();

private:
    Manager *manager = NULL;

    QMdiArea *mdi_area = NULL;

    QMenu *fileMenu = NULL;
    QMenu *viewMenu = NULL;
    QMenu *settingsMenu = NULL;
    QMenu *helpMenu = NULL;

    QAction *loadAct = NULL;
    QAction *saveAct = NULL;
    QAction *exitAct = NULL;

    QAction *consoleViewAct = NULL;
    QAction *measureViewAct = NULL;

    QAction *settingsAct = NULL;

    QAction *aboutAct = NULL;
    QAction *aboutQtAct = NULL;

    void createMenus();
    void createConsoleWnd();
    void createMeasureWnd();
    void createSettingsWnd();

    void closeEvent(QCloseEvent *event) override;

signals:

private slots:
    void handle_menu_loadConfig(bool);
    void handle_menu_saveConfig(bool);
    void handle_menu_exit(bool);
    void handle_menu_settings(bool);
    void handle_menu_about(bool);
    void handle_menu_aboutQt(bool);
    void handle_menu_consoleView(bool);
    void handle_menu_measureView(bool);

    void destroyActions(QObject*);
};

#endif // LCRMEASURE_H
