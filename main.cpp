#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf ("starting\n");

    QApplication a(argc, argv);

    printf ("parser done\n");

    MainWindow w;
    w.show();

    printf ("window shown\n");
    
    return a.exec();
}
