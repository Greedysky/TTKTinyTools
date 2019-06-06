#include <QCoreApplication>
#include "checkerhelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CheckerHelper helper;
    helper.detect("Test");

    return 0;
}
