#include "mainwindow.h"

QString MainWindow::encode(const QString &str)
{
    return QByteArray::toPercentEncoding(str, "/:?=&%");
}

QString MainWindow::decode(const QString &str)
{
    return QByteArray::fromPercentEncoding(str.toUtf8());
}
