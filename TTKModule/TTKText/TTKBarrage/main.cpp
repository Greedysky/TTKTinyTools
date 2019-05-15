#include <QApplication>
#include <QTranslator>

#include "videoview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("cn.qm");
    a.installTranslator(&translator);

    VideoView v;
    v.show();

    return a.exec();
}
