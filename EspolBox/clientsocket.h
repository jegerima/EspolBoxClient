#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QDebug>
#include <QString>

#include <libs.h>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    ClientSocket(QObject *parent, QString ipdir, QString macdir);
    void doConnect();
    void SendString(char *s);

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *sckt;
    QString ip;
    QString mac;
};

#endif // CLIENTSOCKET_H
