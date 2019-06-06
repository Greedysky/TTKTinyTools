#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.toUpper("LOWER");
    w.toLower("UPPER");

    return 0;
}
