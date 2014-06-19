#include "libs.h"

char *QStringToChar(QString str)
{
    QByteArray ba = str.toLatin1();
    char *c = ba.data();
    return c;
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
    QString homePath = getenv("HOME");
    QDir dirFiles(homePath + "/" +dir);
    QStringList allFiles = dirFiles.entryList(QDir::NoDotAndDotDot |
                                              QDir::System |
                                              QDir::Hidden  |
                                              QDir::AllDirs |
                                              QDir::Files, QDir::DirsFirst);
    return allFiles;
}

QFileInfoList getDirectoryInfoFiles(QString dir)
{
    QString homePath = getenv("HOME");
    QDir dirFiles(homePath + "/" +dir);
    QFileInfoList allFiles = dirFiles.entryInfoList(QDir::NoDotAndDotDot |
                                                  QDir::System |
                                                  QDir::Hidden  |
                                                  QDir::AllDirs |
                                                  QDir::Files, QDir::DirsFirst);
    return allFiles;
}
