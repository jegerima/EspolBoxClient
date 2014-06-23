#include "file.h"

file::file(QString name) :QFile(name)
{

}

QString file::calculateHash(QByteArray ba)
{
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

void file::setPath(QString dir)
{
    this->path = dir;
}
