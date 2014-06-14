#ifndef LIBS_H
#define LIBS_H

#include <QDebug>
#include <QString>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


char *QStringToChar(QString str);
int PathExists(QString str);

#endif // LIBS_H
