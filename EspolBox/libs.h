#ifndef LIBS_H
#define LIBS_H

#include <QDir>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFileInfoList>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

char *QStringToChar(QString str);
int PathExists(QString str);
int newDirectory(QString str);
QStringList getDirectoryFiles(QString dir);
QFileInfoList getDirectoryInfoFiles(QString dir);


#endif // LIBS_H
