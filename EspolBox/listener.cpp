#include "listener.h"

Listener::Listener(QString usr, QString pth): QFileSystemWatcher(0)
{
    this->user = new QString(usr);
    this->path = new QString(pth);
    this->DirsList = new QStringList();
    this->FilesList = new QStringList();
    getAllSubDirectories(pth);
    qDebug() << *(this->DirsList);
    getAllFiles();
    qDebug() << *(this->FilesList);
    DirsAddWatch();
    FilesAddWatch();

    connect(this,SIGNAL(directoryChanged(QString)),this,SLOT(showDirModifies(QString)));
    connect(this,SIGNAL(fileChanged(QString)),this,SLOT(showFileModifies(QString)));

}

void Listener::getAllSubDirectories(QString dir)
{
    QDir dirFiles(dir);
    QStringList allDirs = dirFiles.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    for(int i = 0; i<allDirs.size(); i++)
    {
        getAllSubDirectories(dir+"/"+allDirs.at(i));
        this->DirsList->append(dir+"/"+allDirs.at(i));
    }
}

void Listener::getAllFiles()
{
    //Archivos de la raiz
    //qDebug() << "Getting root Files";

    QDir dirFiles(*(this->path));
    QStringList allFiles = dirFiles.entryList(QDir::NoDotAndDotDot |
                                              QDir::System |
                                              QDir::Hidden  |
                                              QDir::Files);
    //qDebug() << "Adding root Files";
    for(int j = 0; j< allFiles.size(); j++)
    {
        //printf(" %d ",j);
        QString FilePath((*(this->path))+"/"+allFiles.at(j));
        this->FilesList->append(FilePath);
    }


    //Archivos de todas las subcarpetas
    //qDebug() << "Getting subdirs files";
    for(int i =0; i< this->DirsList->size(); i++)
    {
        dirFiles = QDir(this->DirsList->at(i));
        allFiles = dirFiles.entryList(QDir::NoDotAndDotDot |
                                                  QDir::System |
                                                  QDir::Hidden  |
                                                  QDir::Files);
        for(int j = 0; j<allFiles.size(); j++)
        {
            QString FullFilePath(this->DirsList->at(i)+"/"+allFiles.at(j));
            this->FilesList->append(FullFilePath);
        }
    }
    //qDebug() << "Completed";
}

void Listener::DirsAddWatch()
{
    this->addPath(*(this->path));
    this->addPaths(*(this->DirsList));
}

void Listener::FilesAddWatch()
{
    this->addPaths(*(this->FilesList));
}

void Listener::showDirModifies(QString data)
{
    qDebug() << "Cambios en " + data;
    QString Carpeta;

    QDir DirTmp(data);
    QStringList allDirsTmp = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    QStringList allFilesTmp = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
    QStringList OldDirs;

    QRegularExpression dir(data+"/(\\w+)");
    QRegularExpression subdirs(data+"/(\\w+)/.*");

    for(int i = 0; i < (this->DirsList->size()); i++)
    {
        QRegularExpressionMatch dirMatch = dir.match(this->DirsList->at(i));
        QRegularExpressionMatch subdirsMatch = subdirs.match(this->DirsList->at(i));

        //qDebug() << subdirsMatch.captured(1);
        if(dirMatch.hasMatch())
        {
            if(!subdirsMatch.hasMatch())
            {
                QString str(dirMatch.captured(1));
                //qDebug() << "Match " + (this->DirsList->at(i));
                OldDirs.append(str);
            }
        }
    }
    OldDirs.sort();
    allDirsTmp.sort();
    qDebug() << "New: " + QString::number(allDirsTmp.size()) +
                " Old: " + QString::number(OldDirs.size());
    qDebug() << allDirsTmp;
    qDebug() << OldDirs;

    if(OldDirs.size()>allDirsTmp.size())
    {
        for(int x=0; x<OldDirs.size(); x++)
        {
            for(int y=0; y<allDirsTmp.size(); y++)
            {
                if(OldDirs.at(x)==allDirsTmp.at(y))
                {
                    x++;
                    y=0;
                }
            }
            Carpeta = OldDirs.at(x);
            x = OldDirs.size();
        }
        qDebug() << "Carpeta "+Carpeta+" eliminada";
    }

    if(OldDirs.size()<allDirsTmp.size())
    {
        for(int x=0; x<allDirsTmp.size(); x++)
        {
            for(int y=0; y<OldDirs.size(); y++)
            {
                if(OldDirs.at(y)==allDirsTmp.at(x))
                {
                    x++;
                    y=0;
                }
            }
            Carpeta = allDirsTmp.at(x);
            x = allDirsTmp.size();
        }
        qDebug() << "Carpeta "+Carpeta+" creada";
    }

    if(OldDirs.size()==allDirsTmp.size())
    {
        qDebug() << "Carpeta renombrada o archivo creado";
    }
}

void Listener::showFileModifies(QString data)
{
    qDebug() << "Archivo "+data+" modificado";
}
