#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#if !TTK_QT_VERSION_CHECK(5,0,0)
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#endif

    QFile file(":/qss/Style3.qss");
    if(file.open(QIODevice::ReadOnly))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
