#include <QApplication>
#include "lcrmeasure.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    LCRMeasure lcr;
    lcr.show();

    return app.exec();
}
