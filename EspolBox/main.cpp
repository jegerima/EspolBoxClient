#include <QCoreApplication>
#include <stdio.h>
#include <QRegularExpression>
#include <textparser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    QString aa("Hola");
    qDebug() << aa;
    char *hh = QStringToChar(aa);
    printf("%s\n",hh);

    textparser z("");
    int j = 0;
    while(j!=-1)
    {
        printf("EspolBox$: ");
        char m[60];
        gets(m);
        QString p(m);
        j = z.parse(p);
    }

    puts("Programa finalizado");

    //getchar();

 //   return a.exec();

    //BUSCAR iNotify*/

    qDebug() << getDirectoryFiles("Descargas");
    qDebug("-----------------");
    //textparser f("hola");
    getOnlyFiles(getDirectoryFiles("Descargas"));
}
