#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.toUtf16("Test");
    w.fromUtf16("Test");

    return 0;
}
