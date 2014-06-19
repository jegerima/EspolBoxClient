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
    QString calculateHash();
    bool openFile();

signals:

public slots:

private:
    QString userName;
    QString hash;

};

#endif // FILE_H
