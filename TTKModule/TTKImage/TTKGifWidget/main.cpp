#include "mainwindow.h"
#include "ttkglobal.h"

#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#ifndef TTK_GREATER_NEW
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
