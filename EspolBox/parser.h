#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QString>
#include <QDataStream>
#include <QStringList>
#include <QRegularExpression>
#include <QFileSystemWatcher>
#include <clientsocket.h>
#include <QThread>
#include <QList>
//#include <file.h>
#include <QDir>

#include <listener.h>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    int parse(QString txt);
    int firstParam(QString txt);
    int secondParam(QString txt, QString usr);

signals:

public slots:
    void serverParse(QString data);
    void showDirModifies(QString data);
    void showFileModifies(QString data);

private:
    QFileSystemWatcher *watcher;
    ClientSocket *cs;
    QThread *hilo;
    QDir *currentDir;
    QString *ip;

    void SetBoxDirToServer();

};

#endif // PARSER_H
