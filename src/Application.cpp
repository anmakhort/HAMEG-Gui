#include <QApplication>
#include <iostream>
#include "../include/LCRGui.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    //app.setAttribute(Qt::AA_DontUseNativeMenuBar);

    LCRGui lcr;
    lcr.show();

    return app.exec();
}
