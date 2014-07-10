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
    bool getStatus();

signals:
    void DataArrived(QString str);

public slots:
    void doConnect();
    void connected();
    void disconnected();
    void readyRead();
    void displayError(QAbstractSocket::SocketError scktError);
    void dataReceived();

private:
    bool online;
    QTcpSocket *sckt;
    QString ip;
    QString mac;
    int ID;
};

#endif // CLIENTSOCKET_H
