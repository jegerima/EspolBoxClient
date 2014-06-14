#include "file.h"
#include <QDebug>

file::file()
{
}

/*
 * http://stackoverflow.com/questions/7430248/creating-a-new-directory-in-c
 */
int file::newDirectory(QString str)
{
    QString homePath = getenv("HOME");
    qDebug() << homePath;

    QString splbxPath = homePath + "/EspolBoxHome";
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



