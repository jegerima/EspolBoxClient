#include <QCoreApplication>
#include <stdio.h>
#include <QRegularExpression>
#include <textparser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << PathExists("/home/jegerima/aa.txt");

    setCURRENT_DIR("/home/jegerima/Descargas");

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

    //BUSCAR iNotify

    /*
    qDebug() << getDirectoryFiles("Descargas");
    qDebug("-----------------");
    //textparser f("hola");
    getOnlyFiles(getDirectoryFiles("Descargas"));
    */
}
