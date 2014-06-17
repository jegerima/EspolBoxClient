#include "textparser.h"
#include <file.h>
#include <QDebug>

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

        file f;
        f.newDirectory(cuser);

        cs->SendString("Crear usuario");
        //cs->bytesWritten();
        return 1;
    }
    if(scdmatch.hasMatch())
    {
        QString user = scdmatch.captured(1);
        qDebug() << user;
        return secondParam(txt);
    }
    qDebug("Digite el parametro correctamente");
    return 0;

}

int textparser::secondParam(QString txt)
{
    QRegularExpression setboxdir(".* -setboxdir (\\w+)");
    QRegularExpression syncbox(".* -syncbox (\\w+)");
    QRegularExpression autosynbox(".* -autosyncbox (\\w+)");
    QRegularExpressionMatch stbxdr = setboxdir.match(txt);
    QRegularExpressionMatch sncbx = syncbox.match(txt);
    QRegularExpressionMatch tsncbx = autosynbox.match(txt);

    if(stbxdr.hasMatch())
    {
        QString boxdir = stbxdr.captured(1);
        qDebug() << "Lanzando funcion -setboxdir " + boxdir;
        return 1;
    }

    if(sncbx.hasMatch())
    {
        QString sync = sncbx.captured(1);
        qDebug() << sync;
        return 1;
    }

    if(tsncbx.hasMatch())
    {
        QString boxdir = stbxdr.captured(1);
        qDebug() << boxdir;
        return 1;
    }
    qDebug("Digite el parametro correctamente");
    return 0;
}
