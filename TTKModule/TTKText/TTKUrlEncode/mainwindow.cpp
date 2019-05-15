#include "mainwindow.h"

#include <QUuid>

QString MainWindow::generateUUID()
{
    return QUuid::createUuid().toString().mid(1, 36);
}
