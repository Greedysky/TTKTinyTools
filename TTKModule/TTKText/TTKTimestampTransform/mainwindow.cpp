#include "mainwindow.h"

#include <QDateTime>

QString MainWindow::currentDateTime()
{
    return QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch() * 1000);
}

QString MainWindow::fromString(const QString &stamp)
{
    if(stamp.length() == 13)
    {
        return QDateTime::fromMSecsSinceEpoch(stamp.toLongLong()).toString(TTK_DATE_TIMES_FORMAT);
    }
    else if(stamp.length() == 10)
    {
        return QDateTime::fromMSecsSinceEpoch(stamp.toInt() * 1000).toString(TTK_DATE_TIMES_FORMAT);
    }
    return {};
}
