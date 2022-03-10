#include "mainwindow.h"

#include <QDateTime>

QString MainWindow::currentDateTimeTimestampString()
{
    return QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch() * 1000);
}

QString MainWindow::dateTimeStringFromTimestampString(const QString &stamp)
{
    if(stamp.length() == 13)
    {
        return QDateTime::fromMSecsSinceEpoch(stamp.toLongLong()).toString("yyyy-MM-dd hh:mm:ss");
    }
    else if(stamp.length() == 10)
    {
        return QDateTime::fromMSecsSinceEpoch(stamp.toInt() * 1000).toString("yyyy-MM-dd hh:mm:ss");
    }
    return QString();
}
