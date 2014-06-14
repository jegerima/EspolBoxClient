//http://www.bogotobogo.com/Qt/Qt5_QTcpSocket_Signals_Slots.php

#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent, QString ipdir, QString macdir) :
    QObject(parent)
{
    this->ip = ipdir;
    this->mac = macdir;
}

void ClientSocket::connected()
{
    qDebug() << "connected...";

    // Hey server, tell me about you.
    sckt->write("Holaaa");
    sckt->write("Hey");
    sckt->write("que");
    sckt->write("Hace");
}

void ClientSocket::disconnected()
{
     qDebug() << "disconnected...";
}

void ClientSocket::doConnect()
{
    sckt = new QTcpSocket(this);

    connect(sckt,SIGNAL(connected()),this,SLOT(connected()));
    connect(sckt,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(sckt,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect(sckt,SIGNAL(readyRead()),this,SLOT(readyRead()));

    qDebug() << "Connecting...";

    //Llamando al server
    qDebug() << "IP: " << this->ip;
    char srvr[20] = "";
    QStringToChar(this->ip);
    printf("Direccion: %s\n",srvr);
    sckt->connectToHost("127.0.0.1",1023);

    //Esperando la respuesta
    if(!sckt->waitForConnected(3022))
    {
        qDebug() << "Error: " << sckt->errorString();
    }
    printf("doConnect()... DONE;\n");
}

void ClientSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void ClientSocket::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << sckt->readAll();
}

void ClientSocket::SendString(char *s)
{
    sckt->write(s);
}
