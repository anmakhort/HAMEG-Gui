#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>
#include <QString>
#include <QChar>
#include <QMap>

class Serializer {
public:
    static const QString VERSION;
    static const QString DEFAULT_PATH;
    static const QString DEFALT_BASEDIR;

    static const QString datetime_path(const QString basedir);

    static void serialize(const QMap<QString,QString> * const map, const QString path);
    static QMap<QString,QString>* deserialize(const QString path);

private:
    static const QChar COMMENT_CHAR;
    static const QString SEPARATOR;
};

#endif // SERIALIZER_H
