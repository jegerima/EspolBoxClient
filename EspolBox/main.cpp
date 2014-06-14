#include <QCoreApplication>
#include <stdio.h>
#include <QRegularExpression>
#include <textparser.h>
#include <file.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    file fl;

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

    //return a.exec();

    //BUSCAR iNotify

}
