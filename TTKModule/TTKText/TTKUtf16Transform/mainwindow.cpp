#include "mainwindow.h"

QString MainWindow::toUtf16(const QString &str)
{
    QString target;
    foreach(const QChar &c, str)
    {
        if(c.unicode() > 0xff)
        {
            target += "\\u";
            target += QString::number(c.unicode(), 16).toUpper().rightJustified(4, '0');
        }
        else
        {
            target += c;
        }
    }

    return target;
}

QString MainWindow::fromUtf16(const QString &str)
{
    QString source = str;
    QString target;
    while(!source.isEmpty())
    {
        if((source.size() >= 6) && source.startsWith("\\u"))
        {
            target += QChar(ushort(source.mid(2, 4).toUShort(nullptr, 16)));
            source.remove(0, 6);
        }
        else
        {
            target += source.at(0);
            source.remove(0, 1);
        }
    }

    return target;
}
