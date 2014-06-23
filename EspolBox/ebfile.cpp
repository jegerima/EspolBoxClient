#include "ebfile.h"

EBFile::EBFile(QString FileName,
               QString RelPath,
               QByteArray FileData)
    //QObject(parent)
{
    this->FileData = FileData;
    this->FileName = FileName;
    this->RelativePath = RelPath;
}

QDataStream &operator<<(QDataStream &out, const EBFile &obj)
{
   out << obj.getFileName() << obj.getRelativePath()
          << obj.getData();
   return out;
}

QDataStream &operator>>(QDataStream &in, EBFile &obj)
{
   QString name;
   QString path;
   QByteArray ba;
   in >> name >> path >> ba;
   obj = EBFile(name,path,ba);
   return in;
}
