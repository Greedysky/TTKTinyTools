#include "pinyinhelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PinyinHelper pinyin;
    qDebug() << pinyin.convertToPinyinString("我们", " ");

    ChineseHelper chinese;
    qDebug() << chinese.convertToTraditionalChinese("我们");

    return 0;
}
