#ifndef EBFILE_H
#define EBFILE_H

#include <QString>
#include <QDataStream>
#include <QByteArray>

class EBFile
{
public:
    EBFile(QString FileName, QString RelPath, QByteArray FileData);
    void setFileName(const QString &fn) {FileName = fn;}
    void setFileData(const QByteArray &ba) {FileData = ba;}
    void setRelativePath(const QString &rp) {RelativePath = rp;}
    QString getRelativePath() const {return RelativePath;}
    QString getFileName() const {return FileName;}
    QByteArray getData() const {return FileData;}
private:
    QString FileName;
    QString RelativePath;
    QByteArray FileData;
};
QDataStream &operator<<(QDataStream &out, const EBFile &obj);
QDataStream &operator>>(QDataStream &in, EBFile &obj);
#endif // EBFILE_H
