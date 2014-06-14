#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include <QString>
#include <QRegularExpression>
#include <clientsocket.h>

class textparser
{
public:
    textparser(QString txt);
    int parse(QString txt);
    int firstParam(QString txt);
    int secondParam(QString txt);

private:
    ClientSocket *cs;
};

#endif // TEXTPARSER_H
