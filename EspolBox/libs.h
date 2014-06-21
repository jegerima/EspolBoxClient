#ifndef LIBS_H
#define LIBS_H

#include <QDir>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QFileInfoList>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

char *QStringToChar(QString str);
int PathExists(QString str);
int newDirectory(QString str);
void setCURRENT_DIR(QString dir);
void setCURRENT_USER(QString usr);
QFile getQFile(QString fl, QString pth);
QString getCURRENT_DIR();
QString getCURRENT_USER();
QString getRELATIVE_DIR();
QList<QByteArray> getFilesInByteArrayList(QStringList ListFiles);
QStringList getDirectoryDirs(QString dir);
QStringList getDirectoryFiles(QString dir);
QFileInfoList getDirectoryInfoFiles(QString dir);
QByteArray QFileToByteArray(QFile fl);


#endif // LIBS_H
