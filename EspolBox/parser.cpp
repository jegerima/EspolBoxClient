#include "parser.h"

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    cs = new ClientSocket(0,QString("192.168.1.6"),QString("Vacila la mac"));
    connect(cs,SIGNAL(DataArrived(QString)),this,SLOT(serverParse(QString)));

    QThread *hilo = new QThread(0);
    this->moveToThread(hilo);
    //connect(hilo,SIGNAL(started()),this,SLOT(doConnect()));
    connect(hilo,SIGNAL(finished()),this,SLOT(deleteLater()));
    connect(this,SIGNAL(destroyed()),hilo,SLOT(quit()));
    hilo->start();
}

int Parser::parse(QString txt)
{
    //Si no hay conexion y desea reconectar
    if(txt== "reconnect" && !cs->getStatus())
    {
        cs = new ClientSocket(0,QString("192.168.1.6"),QString("Vacila la mac"));
        connect(cs,SIGNAL(DataArrived(QString)),this,SLOT(serverParse(QString)));
        return 0;
    }

    //Verifica si el cliente esta conectado al server
    if(!cs->getStatus())
    {
        qDebug() << "No hay conexion. Favor digite 'reconnect'";
        return 0;
    }

    QRegularExpression espolboxc("espolboxc .*");
    QRegularExpressionMatch match = espolboxc.match(txt);

    if(match.hasMatch())//palabra clave espolboxc
    {
        return firstParam(txt);
    }
    else
    {
        if(txt == (QString("exit")))
            return -1;

        if(txt == (QString("help")) || txt == QString("man"))
        {
            qDebug() << "Ayuda no disponible";
            return 0;
        }

        qDebug("Comando no valido. Digite \"help\" pra ayuda.");
        return 0;
    }

    return 0;
}

int Parser::firstParam(QString txt)
{
    QRegularExpression cuser(".* -cuser (\\w+).*");
    QRegularExpression user(".* -user (\\w+).*");
    QRegularExpressionMatch fstmatch = cuser.match(txt);
    QRegularExpressionMatch scdmatch = user.match(txt);
    if(fstmatch.hasMatch())
    {
        QString cuser = fstmatch.captured(1);
        setCURRENT_USER(cuser);
        cs->SendQString("cuser#"+cuser);
        lock();
        return 0;
    }
    if(scdmatch.hasMatch())
    {
        QString user = scdmatch.captured(1);
        qDebug() << user;
        return secondParam(txt,user);
    }

/*    if(txt.at(0)=='#')
    {
        unlock();
        qDebug() << "DESBLOQUEADO";
    }*/
    qDebug("Digite el parametro correctamente");
    return 0;

}

int Parser::secondParam(QString txt, QString usr)
{
    QRegularExpression setboxdir(".* -setboxdir .*");
    QRegularExpression syncbox(".* -syncbox");
    QRegularExpression autosynbox(".* -autosyncbox (\\w+)");
    QRegularExpressionMatch stbxdr = setboxdir.match(txt);
    QRegularExpressionMatch sncbx = syncbox.match(txt);
    QRegularExpressionMatch tsncbx = autosynbox.match(txt);

    QStringList lst = txt.split(" ");

    if(stbxdr.hasMatch()) // SETBOXDIR
    {
        //QString boxdir = stbxdr.captured(1);
        if(PathExists(lst.at(4))==0)
        {
            qDebug() << "Lanzando funcion -setboxdir " + lst.at(4);

            setCURRENT_DIR(lst.at(4));
            setCURRENT_USER(usr);
            cs->SendQString("setboxdir#"+usr+"#"+getRELATIVE_DIR());
            lock();
            return 1;
        }
        else
        {
            qDebug() << "Ruta invalida";
            return 0;
        }
        return 0;
    }

    if(sncbx.hasMatch()) //SYNCBOX
    {
        QString sync = sncbx.captured(1);


    }

    if(tsncbx.hasMatch()) //AUTOSYNCBOX
    {
        QString boxdir = stbxdr.captured(1);
        qDebug() << boxdir;
        cs->SendQString("autosyncbox " + usr);

        return 1;
    }
    qDebug("Digite el parametro correctamente");
    return 0;
}

void getOnlyFiles(QStringList lista)
{
    for(int i =0; i< lista.size();i++)
    {
        QString str = lista.at(i);
        qDebug() << str;
    }
}

void Parser::SetBoxDirToServer()
{
    qDebug() << "Sincronizando " + getCURRENT_DIR();
    QStringList FilesList = getDirectoryFiles(getCURRENT_DIR());
    QStringList DirsList = getDirectoryDirs(getCURRENT_DIR());

    //cs->SendQString("sync#"+usr+"#"+getRELATIVE_DIR());
    QList<QByteArray> baList = getFilesInByteArrayList(FilesList);
    QByteArray baFinal;
    for(int x = 0; x<baList.size(); x++)
    {
        qDebug() << "Sincronizando "+FilesList.at(x);
        qDebug() << "SIZE: " + QString::number(baList.at(x).size());

        baFinal.append(baList.at(x) + '~');
        /*
        QFile fTMP("/home/jegerima/Escritorio/" + FilesList.at(x) + ".txt");
        fTMP.open(QIODevice::WriteOnly);
        fTMP.write(baList.at(x));
        fTMP.close();
        */
    }
    qDebug() << "FINAL SIZE: " + QString::number(baFinal.size());
    cs->SendQByteArray(baFinal);

    QFile fTMP("/home/jegerima/Escritorio/tmp.txt");
    fTMP.open(QIODevice::WriteOnly);
    fTMP.write(baFinal);
    fTMP.close();

    QThread::sleep(2);
    cs->SendQString("syncDONE#syncDONE#syncDONE#syncDONE");
    qDebug() << "Sincronizacion exitosa";
    //return 1;
}

//--------------------------------------------------------

void Parser::serverParse(QString data)
{
    if(data.at(0)=='#')
    {
        QStringList tokens = data.split("#");
        qDebug() << tokens.size();
        if(tokens.at(1)=="cuser")
        {
            if(tokens.at(2)=="ok")
                qDebug() << "Usuario creado exitosamente";
            else
                qDebug() << "Usuario ya existe";
        }

        if(tokens.at(1)=="setboxdir")
        {
            if(tokens.at(2)=="go")
            {
                qDebug() << "Listo para setboxdir";
                SetBoxDirToServer();

                this->watcher = new QFileSystemWatcher(0);
                qDebug() << "Watcher: "+getCURRENT_DIR();
                this->watcher->addPath(getCURRENT_DIR());

                Listener *l = new Listener(getCURRENT_USER(),getCURRENT_DIR());
/*

                Q_FOREACH(QString fl,getFilesListWatcher())
                    this->watcher->addPath(fl);

                QStringList directoryList = this->watcher->directories();
                QStringList filesList = this->watcher->files();

                Q_FOREACH(QString directory,directoryList)
                    qDebug() << "Directory name" << directory << "\n";

                Q_FOREACH(QString files, filesList)
                    qDebug() << "File name: " << files << "\n";

                connect(this->watcher,SIGNAL(directoryChanged(QString)),this,SLOT(showDirModifies(QString)));
                connect(this->watcher,SIGNAL(fileChanged(QString)),this,SLOT(showFileModifies(QString)));
*/
            }
            if(tokens.at(2)=="nouser")
                qDebug() << "Usuario no existe";
            if(tokens.at(2)=="exists")
                qDebug() << "Carpeta ya existe";
        }
    }
    unlock();
}

void Parser::showDirModifies(QString data)
{
    qDebug() << "Cambios en " + data;
}

void Parser::showFileModifies(QString data)
{
    qDebug() << "Archivo "+data+" modificado";
}
