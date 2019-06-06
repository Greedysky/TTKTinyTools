#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.saveIcon("c://Font_Path", 20, 20, 20, 0x2313);

    return 0;
}
