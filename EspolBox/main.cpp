#include <QCoreApplication>
#include <stdio.h>
#include <QRegularExpression>
//#include <textparser.h>
#include <parser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setCURRENT_DIR(getenv("HOME"));
    unlock();
    Parser z(0);

    int j = 0;
    while(j!=-1)
    {
        while(getLock()){}
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

}
