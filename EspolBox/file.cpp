#include "file.h"

file::file(QString name) :QFile(name)
{

}

QString file::calculateHash()
{
    QByteArray ba = this->readAll();
    this->hash = QString(QCryptographicHash::hash(ba,QCryptographicHash::Md5));
    return this->hash;
}

bool file::openFile()
{
    return this->open(QIODevice::ReadOnly);
}

QString file::getHash()
{
    return this->hash;
}
