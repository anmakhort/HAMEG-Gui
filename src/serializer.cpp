#include "../include/serializer.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QDateTime>
#include <QDir>

const QString Serializer::VERSION = QString("Serializer v1.0; by Anatolii Makhort; Software: HAMEG-Gui");
const QString Serializer::DEFAULT_PATH = QString("./hameg.conf");
const QChar Serializer::COMMENT_CHAR = QChar('#');
const QString Serializer::SEPARATOR = QString(": ");
const QString Serializer::DEFALT_BASEDIR = QString("./");

const QString Serializer::datetime_path(const QString basedir) {
    if (!QDir(basedir).exists()) QDir().mkdir(basedir);
    return basedir + QObject::tr("/hameg-") + \
            QDateTime::currentDateTime().toString("dd-MM-yyyy-hh:mm:ss.conf");
}

void Serializer::serialize(const QMap<QString, QString> * const map, const QString path) {
    if (NULL == map || path.size() == 0) return;
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox(QMessageBox::Information, "Error", file.errorString());
        return;
    }
    QTextStream stream(&file);
    stream << Serializer::VERSION << "\n";
    for (auto it = map->begin(); it != map->end(); it++)
        stream << it.key() << Serializer::SEPARATOR << it.value() << "\n";
    stream.flush();
    file.close();
}

QMap<QString,QString>* Serializer::deserialize(const QString path) {
    if (path.size() == 0) return NULL;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox(QMessageBox::Information, "Error", file.errorString());
        return NULL;
    }
    QTextStream stream(&file);
    QString line = stream.readLine();
    if (line != Serializer::VERSION) {
        file.close();
        QMessageBox(QMessageBox::Information, "Error", "Invalid file format or serializer version");
        return NULL;
    }
    QMap<QString,QString> *map = new QMap<QString,QString>();
    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.size() <= 1 || line[0] == Serializer::COMMENT_CHAR) continue;
        QStringList lst = line.split(Serializer::SEPARATOR);
        if (!lst.empty() && lst.size() == 2) {
            (*map)[lst[0]] = lst[1];
        } else {
            delete map;
            file.close();
            QMessageBox(QMessageBox::Information, "Error", "Invalid file format!");
            return NULL;
        }
    }
    file.close();
    return map;
}
