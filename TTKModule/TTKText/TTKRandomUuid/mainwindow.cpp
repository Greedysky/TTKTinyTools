#include "mainwindow.h"

#include <QUrl>

QString MainWindow::encode(const QString &str)
{
    return QUrl::toPercentEncoding(str, "/:?=&%");
}

QString MainWindow::decode(const QString &str)
{
    return QUrl::fromPercentEncoding(str.toUtf8());
}
