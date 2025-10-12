#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setSource("Test");
    w.calculateMD5();

//    return a.exec();
    Q_UNUSED(a);
    return EXIT_SUCCESS;
}
