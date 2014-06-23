#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QCryptographicHash>

class file : public QFile
{
    Q_OBJECT
public:
    //explicit file(QObject *parent = 0);
    file(QString name);

    QString getHash();
    QString calculateHash(QByteArray ba);
    void setPath(QString dir);
    bool openFile();

signals:

public slots:

private:
    QString name;
    QString path;
    QString userName;
    QString hash;

};

#endif // FILE_H
