#ifndef LISTENER_H
#define LISTENER_H

#include <QFileSystemWatcher>
#include <QRegularExpression>
#include <QStringList>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QList>
#include <QDir>

class Listener: public QFileSystemWatcher
{
    Q_OBJECT
public:
    Listener(QString usr, QString pth);

public slots:
    void showDirModifies(QString data);
    void showFileModifies(QString data);

private:
    QString *path;
    QString *user;
    QStringList *FilesList;
    QStringList *DirsList;

    void getAllSubDirectories(QString dir);
    void getAllFiles();
    void DirsAddWatch();
    void FilesAddWatch();
};

#endif // LISTENER_H
