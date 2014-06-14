#ifndef FILE_H
#define FILE_H

#include <libs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <QString>
#include <QDateTime>

class file
{
   // Q_OBJECT

public:
    file();
    int newDirectory(QString str);
    //Procedimientos
    //Funciones
signals:

private slots:

private:
    QString name;
    QDateTime date;
    int fileSize;
};

#endif // FILE_H
