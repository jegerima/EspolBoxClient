#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QJsonObject>
#include <QDebug>
#include <QString>
#include <QByteArray>

#include <libs.h>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    ClientSocket(QObject *parent, QString ipdir, QString macdir);
    ~ClientSocket();
    void SendQString(QString qs);
    void SendQByteArray(QByteArray ba);

signals:

public slots:
    void doConnect();
    void connected();
    void disconnected();
    void readyRead();
    void displayError(QAbstractSocket::SocketError scktError);

private:
    QTcpSocket *sckt;
    QString ip;
    QString mac;
    int ID;
};

#endif // CLIENTSOCKET_H
