#include <QApplication>
#include <QTranslator>

#include "videoview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    if(!translator.load("cn.qm"))
    {
        qWarning("Load translation error");
    }
    a.installTranslator(&translator);

    VideoView v;
    v.show();

    return a.exec();
}
