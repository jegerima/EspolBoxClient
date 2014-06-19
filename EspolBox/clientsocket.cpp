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

    // Hey server, tell me about you.
    sckt->write("Funciona Carajo!");
    qDebug() << "Mensajes enviados.";
}

void ClientSocket::disconnected()
{
     qDebug() << "disconnected...";
}

void ClientSocket::doConnect()
{
    connect(sckt,SIGNAL(connected()),this, SLOT(connected()));
    connect(sckt,SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(sckt,SIGNAL(readyRead()),this, SLOT(readyRead()));
    //connect(sckt,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    qDebug() << "Connecting...";

    //Llamando al server
    qDebug() << "IP: " << this->ip;
    sckt->connectToHost("127.0.0.1",1023);

    //Esperando la respuesta

    if(!sckt->waitForConnected(3000))//ms
    {
        qDebug() << "Error: " << sckt->errorString();
        return;
    }

    printf("doConnect()... DONE;\n");
    qDebug() << sckt->isValid();
    qDebug() << sckt->isOpen();
    qDebug() << sckt->isReadable();
    qDebug() << sckt->isWritable();
}

void ClientSocket::readyRead()
{
    qDebug() << "Reading...";
    // read the data from the socket
    qDebug() << sckt->readAll();
}

void ClientSocket::SendString(QString qs)
{
    sckt->write(QStringToChar(qs));
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
