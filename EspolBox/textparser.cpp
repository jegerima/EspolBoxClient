#include "textparser.h"
#include <QDebug>
#include <QFile>

textparser::textparser(QString txt)
{
    cs = new ClientSocket(0,QString("192.168.1.6"),QString("Vacila la mac"));
}

int textparser::parse(QString txt)
{
    QRegularExpression espolboxc("espolboxc .*");
    QRegularExpressionMatch match = espolboxc.match(txt);
    if(match.hasMatch())
    {
        return firstParam(txt);
    }
    else
    {
        if(txt == (QString("exit")))
            return -1;

        if(txt == (QString("help")))
        {
            qDebug() << "Ayuda no disponible";
            return 0;
        }

        qDebug("Comando no valido. Digite \"help\" pra ayuda.");
        return 0;
    }

    return 0;
}

int textparser::firstParam(QString txt)
{
    QRegularExpression cuser(".* -cuser (\\w+).*");
    QRegularExpression user(".* -user (\\w+).*");
    QRegularExpressionMatch fstmatch = cuser.match(txt);
    QRegularExpressionMatch scdmatch = user.match(txt);
    if(fstmatch.hasMatch())
    {
        QString cuser = fstmatch.captured(1);
        qDebug() <<"-cuser "+cuser;

        newDirectory(cuser);
        cs->SendQString("cuser "+cuser);
        return 1;
    }
    if(scdmatch.hasMatch())
    {
        QString user = scdmatch.captured(1);
        qDebug() << user;
        return secondParam(txt,user);
    }
    qDebug("Digite el parametro correctamente");
    return 0;

}

int textparser::secondParam(QString txt, QString usr)
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
            cs->SendQString("setboxdir "+usr+" "+getRELATIVE_DIR());
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
        qDebug() << "Sincronizando " + getCURRENT_DIR();
        QStringList FilesList = getDirectoryFiles(getCURRENT_DIR());
        qDebug() << "Archivos:";
        qDebug() << FilesList;
        QStringList DirsList = getDirectoryDirs(getCURRENT_DIR());
        qDebug() << "Directorios:";
        qDebug() << DirsList;

        cs->SendQString("sync#"+usr+"#"+getRELATIVE_DIR());
        QList<QByteArray> baList = getFilesInByteArrayList(FilesList);
        for(int x = 0; x<baList.size(); x++)
        {
            cs->SendQByteArray(baList.at(x));
            QThread::msleep(500);
        }
        cs->SendQString("syncDONE#syncDONE");
        cs->SendQString("syncDONE#syncDONE");
        return 1;
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
