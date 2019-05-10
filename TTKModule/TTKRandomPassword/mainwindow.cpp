#include "mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow()
{
    srand(QDateTime::currentDateTime().toMSecsSinceEpoch());
}

QString MainWindow::randomPassword(const int length, const bool number, const bool english, const bool caseSensitive)
{
    QString password;
    QString table;

    const QString numberTable = "0123456789";
    const QString lowercaseCharacters = "abcdefghijklmnopqrstuvwxyz";
    const QString upperCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if(number)
    {
        table += numberTable;
    }

    if(english)
    {
        if(caseSensitive)
        {
            table += lowercaseCharacters;
            table += upperCharacters;
        }
        else
        {
            table += lowercaseCharacters;
        }
    }

    if(table.isEmpty())
    {
        return QString();
    }

    for(int index = 0; index < length; ++index)
    {
        password += table.at(rand() % table.size());
    }

    return password;
}
