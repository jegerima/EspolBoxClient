//http://www.bogotobogo.com/Qt/Qt5_QTcpSocket_Signals_Slots.php

#include "clientsocket.h"
#include <QThread>

ClientSocket::ClientSocket(QObject *parent, QString ipdir, QString macdir) :
    QObject(parent)
{
    this->ip = ipdir;
    this->mac = macdir;
    sckt = new QTcpSocket(this);

    QThread *hilo = new QThread(0);
    this->moveToThread(hilo);
    connect(hilo,SIGNAL(started()),this,SLOT(doConnect()));
    connect(hilo,SIGNAL(finished()),this,SLOT(deleteLater()));
    connect(this,SIGNAL(destroyed()),hilo,SLOT(quit()));
    hilo->start();

   // hilo->exec();
}

ClientSocket::~ClientSocket()
{
    sckt->close();
}

void ClientSocket::connected()
{
    qDebug() << "Conectado!";
}

void ClientSocket::disconnected()
{
     qDebug() << "Desconectado";
}

void ClientSocket::doConnect()
{
    connect(sckt,SIGNAL(connected()),this, SLOT(connected()));
    connect(sckt,SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(sckt,SIGNAL(readyRead()),this, SLOT(readyRead()));
    //connect(sckt,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    qDebug() << "Conectando...";

    //Llamando al server
    qDebug() << "IP: " << this->ip;
    sckt->connectToHost("127.0.0.1",1022);

    //Esperando la respuesta

    if(!sckt->waitForConnected(3000))//ms
    {
        qDebug() << "Error: " << sckt->errorString();
        return;
    }
    /*
    qDebug() << sckt->isValid();
    qDebug() << sckt->isOpen();
    qDebug() << sckt->isReadable();
    qDebug() << sckt->isWritable();
    */
}

void ClientSocket::readyRead()
{
    // read the data from the socket
    qDebug() << "Server: " + sckt->readAll();
}

void ClientSocket::SendQString(QString qs)
{
    sckt->write(QStringToChar(qs));
}

void ClientSocket::SendQByteArray(QByteArray ba)
{
    sckt->write(ba);
}

void ClientSocket::displayError(QAbstractSocket::SocketError scktError)
{
    switch (scktError) {
         case QAbstractSocket::RemoteHostClosedError:
             break;
         case QAbstractSocket::HostNotFoundError:
             qDebug("Host no encontrado.");
             break;
         case QAbstractSocket::ConnectionRefusedError:
             qDebug("Conexion rechazada por el servidor.");
             break;
         default:
             qDebug() << ("The following error occurred: 0");
         }
}
