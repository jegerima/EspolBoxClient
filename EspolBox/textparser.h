#ifndef TEXTPARSER_H
#define TEXTPARSER_H


#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <clientsocket.h>
#include <QThread>
#include <QList>
#include <file.h>
#include <QDir>

class textparser
{
public:
    textparser(QString txt);
    int parse(QString txt);
    int firstParam(QString txt);
    int secondParam(QString txt);


private:
    ClientSocket *cs;
    QThread *hilo;
    QDir *currentDir;
    QList<file> *currentFiles;
};

void getOnlyFiles(QStringList lista);

#endif // TEXTPARSER_H
