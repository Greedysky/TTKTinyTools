#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.currentDateTime();

//    return a.exec();
    Q_UNUSED(a);
    return EXIT_SUCCESS;
}
