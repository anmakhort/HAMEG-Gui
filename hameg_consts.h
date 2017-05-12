#ifndef HAMEG_CONSTS_H
#define HAMEG_CONSTS_H

#include <QString>
#include <QMap>

static const unsigned int FREQs[] = {   20, 24, 25, 30, 36, 40, 45, 50, 60, 72, 75, 80,
                                        90, 100, 120, 150, 180, 200, 240, 250, 300, 360, 400, 450,
                                        500, 600, 720, 750, 800, 900, 1000, 1200, 1500, 1800, 2000, 2400,
                                        2500, 3000, 3600, 4000, 4500, 5000, 6000, 7200, 7500, 8000, 9000, 10000,
                                        12000, 15000, 18000, 20000, 24000, 25000, 30000, 36000, 40000, 45000, 50000, 60000,
                                        72000, 75000, 80000, 90000, 100000, 120000, 150000, 180000, 200000  };


static const QString FUNCs[] = {    tr("Ls-Q"), tr("Lp-Rp"), tr("Cs-Rs"), tr("Rp-Q"), tr("R-X"),
                                    tr("Lp-Q"), tr("Cs-D"), tr("Cp-Rp"), tr("Z-O"), tr("G-B"),
                                    tr("Ls-Rs"), tr("Cp-D"), tr("Rs-Q"), tr("Y-O")  };  // 'O' means \Theta

static const QString COMMAND_END = tr("\r"); // or "\r\n" [CR+LF or CR]


static QMap<QString, QString> _init_commands() {
    QMap<QString, QString> comms;

    comms["Identification"] = "*IDN?"; // HAMEG Instruments,<instrument type>,<serial number>,<firmware>
    comms["Reset"] = "*RST";
    comms["Operation Complete"] = "*OPC?"; // Returns 1 when all measurements successfully completed
    comms["Sync Wait Completing"] = "*WAI"; // STRT -> *WAI -> XALL?  - start meas and wait compl and send the results
    comms["Save Conf to Memory"] = "*SAV %i"; // %i between 0 and 9
    comms["Load Conf from Memory"] = "*RCL %i";
    comms["Lock Panel"] = "LOCK 1";
    comms["Unlock Panel"] = "LOCK 0";
    comms[""] = "";
    comms[""] = "";
    comms[""] = "";
    comms[""] = "";
    comms[""] = "";

    return comms;
}
static const QMap<QString, QString> COMMANDS = _init_commands();



#endif // HAMEG_CONSTS_H






