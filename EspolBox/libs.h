#ifndef LIBS_H
#define LIBS_H

#include <QDir>
#include <QHash>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QFileInfoList>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <file.h>
#include <stdlib.h>

char *QStringToChar(QString str);
int PathExists(QString str);
int newDirectory(QString str);
void setCURRENT_DIR(QString dir);
void setCURRENT_USER(QString usr);
void lock();
void unlock();
bool getLock();

QFile getQFile(QString fl, QString pth);
QString getCURRENT_DIR();
QString getCURRENT_USER();
QString getRELATIVE_DIR();
QString calculateHash(QByteArray ba);
QList<QByteArray> getFilesInByteArrayList(QStringList ListFiles);
QStringList getDirectoryDirs(QString dir);
QStringList getDirectoryFiles(QString dir);
QFileInfoList getDirectoryInfoFiles(QString dir);
QByteArray QFileToByteArray(QFile fl);

void addDirToWatch(QString dir);
void addFileToWatch(QString file);
QStringList getDirsListWatcher();
QStringList getFilesListWatcher();

#endif // LIBS_H
