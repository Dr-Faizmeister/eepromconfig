#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf ("starting\n");

    QApplication a(argc, argv);

    DomParser parser;
    parser.readFile("C:/Qt/proj/eeprom/eepromconf/config.xml");

    printf ("parser done\n");

    MainWindow w;
    w.show();

    printf ("window shown\n");
    
    return a.exec();
}
