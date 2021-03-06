#include "libs.h"
#include "ebfile.h"

QString CURRENT_DIR;
QString RELATIVE_DIR;
QString CURRENT_USER;

QStringList DirsListWatcher;
QStringList FilesListWatcher;

bool block;

char *QStringToChar(QString str)
{
    QByteArray ba = str.toLatin1();
    char *c = ba.data();
    return c;
}

void lock()
{
    block = true;
}

void unlock()
{
    block = false;
}

bool getLock()
{
    return block;
}
/*
 * Devuelve -1 si la ruta no existe
 * Caso contrario devuelve 0
 */
int PathExists(QString str)
{
    //http://linux.die.net/man/2/mkdir

    struct stat st = {0};
    return stat(QStringToChar(str),&st);
}

int newDirectory(QString str)
{
    QString homePath = getenv("HOME");
    qDebug() << homePath;

    QString splbxPath = homePath + "/EspolBox";
    qDebug() << splbxPath;

    if(PathExists(splbxPath) == -1)
    {
        mkdir(QStringToChar(splbxPath),0700);
        qDebug() << "Creando directorio: " + splbxPath;
    }

    QString path = splbxPath + "/" + str;
    qDebug() << path;

    if(PathExists(path) == -1)
    {
        //http://linux.die.net/man/2/stat

        mkdir(QStringToChar(path),0700);
        printf("Directorio creado exitosamente\n");
        return 1;
    }
    else
    {
        printf("Directorio existente\n");
    }
    return 0;
}

QStringList getDirectoryFiles(QString dir)
{
    //QString homePath = getenv("HOME");
    //QDir dirFiles(homePath + "/" +dir);
    QDir dirFiles(dir);
    QStringList allFiles = dirFiles.entryList(QDir::NoDotAndDotDot |
                                              QDir::System |
                                              QDir::Hidden  |
                                              QDir::Files);
    return allFiles;
}

QStringList getDirectoryDirs(QString dir)
{
    QDir dirFiles(dir);
    QStringList allDirs = dirFiles.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    return allDirs;
}

QFileInfoList getDirectoryInfoFiles(QString dir)
{
    QDir dirFiles(dir);
    QFileInfoList allFiles = dirFiles.entryInfoList(QDir::NoDotAndDotDot |
                                                  QDir::System |
                                                  QDir::Hidden  |
                                                  QDir::Files, QDir::DirsFirst);
    return allFiles;
}

QByteArray QFileToByteArray(QFile fl)
{
      QByteArray dataFile(fl.readAll());
      return dataFile;
}
/*
QFile getQFile(QString fl, QString pth)
{
    qDebug() << pth;
    QFile File(pth);
    if(PathExists(pth)==1)
    {
        if(!File.open(QIODevice::ReadOnly))
        {
            qDebug() << "Error opening file";
        }
        else
        {
            qDebug() << "File " + pth +" no exists";
        }
    }
    return File;
}
*/
void setCURRENT_DIR(QString dir)
{
    CURRENT_DIR = dir;
    RELATIVE_DIR = dir.remove(getenv("HOME"));
}

void setCURRENT_USER(QString usr)
{
    CURRENT_USER = usr;
}

QString getCURRENT_DIR()
{
    return CURRENT_DIR;
}

QString getCURRENT_USER()
{
    return CURRENT_USER;
}

QString getRELATIVE_DIR()
{
    return RELATIVE_DIR;
}

QList<QByteArray> getFilesInByteArrayList(QStringList ListFiles)
{
    QList<QByteArray> BytesList;
    int i = 0;
    for(i=0; i<ListFiles.size(); i++)
    {
        QString FileFullPath(getCURRENT_DIR()+"/"+ListFiles.at(i));
        addFileToWatch(FileFullPath);
        qDebug() << "Archivo "+ FileFullPath;
        QFile f(FileFullPath);
        f.open(QIODevice::ReadOnly);

        QByteArray ba = getCURRENT_USER().toLatin1()+ "%" + getRELATIVE_DIR().toLatin1() + "%" + ListFiles.at(i).toLatin1() + "%"+f.readAll();
        BytesList.append(ba);

        f.close();
    }
    return BytesList;
}

QString calculateHash(QByteArray ba)
{
    QString hash(QCryptographicHash::hash(ba,QCryptographicHash::Md5));
    return hash;
}

void addDirToWatch(QString dir)
{
    DirsListWatcher.append(dir);
}

void addFileToWatch(QString file)
{
    FilesListWatcher.append(file);
}

QStringList getDirsListWatcher()
{
    return DirsListWatcher;
}

QStringList getFilesListWatcher()
{
    return FilesListWatcher;
}
