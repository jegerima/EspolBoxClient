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
    //qDebug() << "Cambios en " + data;
    QString Carpeta;

    QDir DirTmp(data);
    QStringList allDirsTmp = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
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
    //qDebug() << "New: " + QString::number(allDirsTmp.size()) +" Old: " + QString::number(OldDirs.size());
    //qDebug() << allDirsTmp;
    //qDebug() << OldDirs;

    if(OldDirs.size()>allDirsTmp.size()) //Carpeta Elimidada
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
            x = OldDirs.size(); //sale del for
        }
        qDebug() << "Carpeta "+data+"/"+Carpeta+" eliminada";
        refactorAllWatchers();
        emit comandToServer("rmdir#"+*(this->user)+"#"+data+"/"+Carpeta);
        return;
    }

    if(OldDirs.size()<allDirsTmp.size()) //Carpeta Creada
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
            Carpeta = allDirsTmp.at(x); //nombre de la carpeta
            x = allDirsTmp.size(); //sale del for
        }
        qDebug() << "Carpeta "+data+"/"+Carpeta+" creada";
        //addDirToList(data+"/"+Carpeta);
        refactorAllWatchers();
        emit comandToServer("mkdir#"+*(this->user)+"#"+data+"/"+Carpeta);
        return;
    }


    if(OldDirs.size()==allDirsTmp.size())  //Carpeta renombrada, archivo creado o archivo eliminado
    {
        //qDebug() << "Carpeta renombrada, archivo creado o archivo eliminado";


        bool DirRenamed;
        QString oldDir, newDir;

        for(int x=0; x<OldDirs.size(); x++)
        {
            for(int y=0; y<allDirsTmp.size(); y++)
            {
                DirRenamed = true;
                if(OldDirs.at(x)==allDirsTmp.at(y))
                {
                    DirRenamed = false;
                    y = allDirsTmp.size();
                }
            }
            if(DirRenamed)
            {
                oldDir = OldDirs.at(x);
                //qDebug() << oldDir;
            }
        }

        for(int x=0; x<allDirsTmp.size(); x++)
        {
            for(int y=0; y<OldDirs.size(); y++)
            {
                DirRenamed = true;
                if(allDirsTmp.at(x)==OldDirs.at(y))
                {
                    DirRenamed = false;
                    y = OldDirs.size();
                }
            }
            if(DirRenamed)
            {
                newDir = allDirsTmp.at(x);
                //qDebug() << newDir;
            }
        }

        if(oldDir.isNull() && newDir.isNull())
        {
            //qDebug() << "Archivo eliminado, creado o renombrado";
            showDirFilesModifies(data);
            refactorAllWatchers();
        }
        else
        {
            //int index = this->DirsList->indexOf(data+"/"+oldDir);
            //this->DirsList->removeAt(index);
            refactorAllWatchers();

            //removeWatcherDirAndContents(data+"/"+oldDir);
            qDebug() << "Carpeta "+oldDir + " renombrada a "+newDir;
            emit comandToServer("renamedir#"+(*(this->user))+"#"+data+"/"+oldDir+"#"+data+"/"+newDir);
            //addWatcherDirAndContents(data+"/"+newDir);
        }

        return;
    }
    return;
}

void Listener::showFileModifies(QString data)
{
    qDebug() << "Archivo "+data+" modificado";
}

void Listener::removeWatchersAndDirsRecursive(QString dir)
{
    QDir DirTmp(dir);
    QStringList allDirs = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    QStringList allFiles = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);

    for(int i=0; i<allDirs.size(); i++)
    {
        int index = this->DirsList->indexOf(dir+"/"+allDirs.at(i));
        if(index==-1) qDebug()<< "DIR NOT FOUND "+ dir +"/"+allDirs.at(i);
        this->DirsList->removeAt(index);
        removeWatchersAndDirsRecursive(dir+"/"+allDirs.at(i));
    }

    for(int j=0; j<allFiles.size(); j++)
    {
        int index = this->FilesList->indexOf(dir+"/"+allFiles.at(j));
        if(index==-1) qDebug()<< "FILE NOT FOUND "+ dir +"/"+allFiles.at(j);
        this->DirsList->removeAt(index);
        //removeWatcherDirAndContents(dir+"/"+allFiles.at(i));
    }
}

void Listener::addWatchersAndDirsRecursive(QString dir)
{
    QDir DirTmp(dir);
    QStringList allDirs = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    QStringList allFiles = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);

    for(int i=0; i<allDirs.size(); i++)
    {
        int index = this->DirsList->indexOf(dir+"/"+allDirs.at(i));
        if(index==-1) qDebug()<< "DIR NOT FOUND "+ dir +"/"+allDirs.at(i);
        this->DirsList->removeAt(index);
        removeWatchersAndDirsRecursive(dir+"/"+allDirs.at(i));
    }

    for(int j=0; j<allFiles.size(); j++)
    {
        int index = this->FilesList->indexOf(dir+"/"+allFiles.at(j));
        if(index==-1) qDebug()<< "FILE NOT FOUND "+ dir +"/"+allFiles.at(j);
        this->DirsList->removeAt(index);
        //removeWatcherDirAndContents(dir+"/"+allFiles.at(i));
    }
}

/*
 * Remueve un Directorio, sus subdirectorios de la lista
 * Tambien remueve su watcher y sus subWatchers
 */
void Listener::removeDirFromList(QString fullPath)
{
    int index = this->DirsList->indexOf(fullPath);
    this->DirsList->removeAt(index);
    this->removePath(fullPath);

    removeWatchersAndDirsRecursive(fullPath);
}

/*
 * Agrega un Directorio a la lista y un Watcher
 */
void Listener::addDirToList(QString fullPath)
{
    this->addPath(fullPath);
    this->DirsList->append(fullPath);
}

void Listener::refactorAllWatchers()
{
    this->DirsList->clear();
    this->FilesList->clear();

    this->removePaths(this->directories());
    this->removePaths(this->files());

    getAllSubDirectories(*(this->path));
    getAllFiles();

    DirsAddWatch();
    FilesAddWatch();
}

void Listener::showDirFilesModifies(QString data)
{
    QString Archivo;

    QDir DirTmp(data);
    QStringList allFilesTmp = DirTmp.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files);
    QStringList OldFiles;

    //qDebug() << "data: "+data;
    QRegularExpression file(data+"/(\\w+)");
    //QRegularExpression subdirs(data+"/(\\w+)/.*");

    for(int i = 0; i < (this->FilesList->size()); i++)
    {
        QRegularExpressionMatch FileMatch = file.match(this->FilesList->at(i));
        //QRegularExpressionMatch subdirsMatch = subdirs.match(this->DirsList->at(i));

        //qDebug() << subdirsMatch.captured(1);
        if(FileMatch.hasMatch())
        {
            Archivo = FileMatch.captured(1);
            //qDebug() << "Match " + (this->FilesList->at(i)) + " " +Archivo;
            OldFiles.append(Archivo);
        }
    }

    OldFiles.sort();
    allFilesTmp.sort();

    int nNew = allFilesTmp.size();
    int nOld = OldFiles.size();

    //qDebug() << "New: " + QString::number(nNew) + " Old: " + QString::number(nOld);
    //qDebug() << allFilesTmp;
    //qDebug() << OldFiles;

    QString oldFile, newFile;


    bool FileRenamed;


    for(int x=0; x<OldFiles.size(); x++)
    {
        for(int y=0; y<allFilesTmp.size(); y++)
        {
            FileRenamed = true;
            if(OldFiles.at(x)==allFilesTmp.at(y))
            {
                FileRenamed = false;
                y = allFilesTmp.size();
            }
        }
        if(FileRenamed)
        {
            oldFile = OldFiles.at(x);
            //qDebug() << oldDir;
        }
    }

    for(int x=0; x<allFilesTmp.size(); x++)
    {
        for(int y=0; y<OldFiles.size(); y++)
        {
            FileRenamed = true;
            if(allFilesTmp.at(x)==OldFiles.at(y))
            {
                FileRenamed = false;
                y = OldFiles.size();
            }
        }
        if(FileRenamed)
        {
            newFile = allFilesTmp.at(x);
            //qDebug() << newDir;
        }
    }

    /*
    if(oldFile.isNull() && newFile.isNull())
    {
        qDebug() << "Archivo "+oldFile +" renombrado a "+newFile;
        emit comandToServer("renameFile#"+this->user+"#"+data+"/"+OldFile+"#"+data+"/"+newFile);
        //showDirFilesModifies(data);
        //refactorAllWatchers();
    }
    */

    if(nNew == nOld)
    {
        qDebug() << "Archivo "+ oldFile+ " renombrado por "+newFile;
        emit comandToServer("renameFile#"+(*(this->user))+"#"+data+"/"+oldFile+"#"+data+"/"+newFile);
        return;
    }

    if(nNew > nOld)
    {
        qDebug() << "Archivo "+ newFile+ " creado";
        emit comandToServer("mkFile#"+(*(this->user))+"#"+data+"/"+newFile);
        return;
    }

    if(nNew < nOld)
    {
        qDebug() << "Archivo "+ oldFile + ".txt eliminado";
        emit comandToServer("mkFile#"+(*(this->user))+"#"+data+"/"+oldFile);
        return;
    }
}
