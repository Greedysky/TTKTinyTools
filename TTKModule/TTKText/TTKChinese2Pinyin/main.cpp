#include "pinyinhelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PinyinHelper pinyin;
    pinyin.convertToPinyinString("我们", " ");

    ChineseHelper chinese;
    chinese.convertToTraditionalChinese("我们");

    return 0;
}
