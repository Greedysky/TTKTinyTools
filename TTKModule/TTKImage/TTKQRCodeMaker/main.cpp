#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.savePng("1111111111111");

//    return a.exec();
    Q_UNUSED(a);
    return EXIT_SUCCESS;
}
