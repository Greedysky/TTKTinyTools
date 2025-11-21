#include <QApplication>
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
#  include <QTextCodec>
#endif
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if !TTK_QT_VERSION_CHECK(6,0,0)
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#  if !TTK_QT_VERSION_CHECK(5,0,0)
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#  endif
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
