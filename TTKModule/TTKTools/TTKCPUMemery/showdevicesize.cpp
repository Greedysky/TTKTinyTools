#include "showdevicesize.h"
#include <QProcess>
#include <QTableWidget>
#include <QFileInfo>
#include <QHeaderView>
#include <QDir>
#include <QProgressBar>

#ifdef Q_OS_WIN
#include "windows.h"
#endif
#define GB (1024 * 1024 * 1024)
#define MB (1024 * 1024)
#define KB (1024)

ShowDeviceSize *ShowDeviceSize::m_instance = nullptr;
ShowDeviceSize::ShowDeviceSize(QObject *parent) : QObject(parent)
{
    m_process = new QProcess(this);
    connect(m_process, SIGNAL(readyRead()), this, SLOT(readData()));
}

void ShowDeviceSize::setTableWidget(QTableWidget *table)
{
    m_tableWidget = table;
    m_tableWidget->clear();

    m_tableWidget->setColumnCount(5);
    m_tableWidget->setColumnWidth(0, 100);
    m_tableWidget->setColumnWidth(1, 100);
    m_tableWidget->setColumnWidth(2, 100);
    m_tableWidget->setColumnWidth(3, 100);
    m_tableWidget->setColumnWidth(4, 150);

    m_tableWidget->setStyleSheet("QTableWidget::item{padding:0px;}");

    QStringList headText;
    headText << "Dir" << "Used" << "Available" << "Size" << "Percent" ;
    m_tableWidget->setHorizontalHeaderLabels(headText);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->verticalHeader()->setVisible(true);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void ShowDeviceSize::load()
{
    for(int i = 0; i < m_tableWidget->rowCount(); i++)
    {
        m_tableWidget->removeRow(0);
    }

#ifdef Q_OS_WIN
    const QFileInfoList &list = QDir::drives();
    foreach(const QFileInfo &dir, list)
    {
        const QString &dirName = dir.absolutePath();
        LPCWSTR lpcwstrDriver = (LPCWSTR)dirName.utf16();
        ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
        if(GetDiskFreeSpaceEx(lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes))
        {
            QString use = QString::number(static_cast<double>(liTotalBytes.QuadPart - liTotalFreeBytes.QuadPart) / GB, 'f', 1);
            use += "G";
            QString free = QString::number(static_cast<double>(liTotalFreeBytes.QuadPart) / GB, 'f', 1);
            free += "G";
            QString all = QString::number(static_cast<double>(liTotalBytes.QuadPart) / GB, 'f', 1);
            all += "G";
            int percent = 100 - ((double)liTotalFreeBytes.QuadPart / liTotalBytes.QuadPart) * 100;

            insertSize(dirName, use, free, all, percent);
        }
    }
#else
    m_process->start("df -h");
#endif
}

void ShowDeviceSize::readData()
{
    while(!m_process->atEnd())
    {
        const QString &result = QLatin1String(m_process->readLine());
        if(result.startsWith("/dev/sda"))
        {
            checkSize(result, "");
        }
    }
}

void ShowDeviceSize::checkSize(const QString &result, const QString &name)
{
    QString dev, use, free, all;
    int percent = 0;
    QStringList list = result.split(" ");
    int index = 0;

    for(int i = 0; i < list.count(); i++)
    {
        QString s = list.at(i).trimmed();
        if(s == "")
        {
            continue;
        }
        index++;

        if(index == 1)
        {
            dev = s;
        }
        else if(index == 2)
        {
            all = s;
        }
        else if(index == 3)
        {
            use = s;
        }
        else if(index == 4)
        {
            free = s;
        }
        else if(index == 5)
        {
            percent = s.left(s.length() - 1).toInt();
            break;
        }
    }

    if(name.length() > 0)
    {
        dev = name;
    }

    insertSize(dev, use, free, all, percent);
}

void ShowDeviceSize::insertSize(const QString &name, const QString &use, const QString &free, const QString &all, int percent)
{
    int row = m_tableWidget->rowCount();
    m_tableWidget->insertRow(row);
    m_tableWidget->setRowHeight(row, 25);

    QTableWidgetItem *itemname = new QTableWidgetItem(name);
    QTableWidgetItem *itemuse = new QTableWidgetItem(use);
    itemuse->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *itemfree = new QTableWidgetItem(free);
    itemfree->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *itemall = new QTableWidgetItem(all);
    itemall->setTextAlignment(Qt::AlignCenter);

    m_tableWidget->setItem(row, 0, itemname);
    m_tableWidget->setItem(row, 1, itemuse);
    m_tableWidget->setItem(row, 2, itemfree);
    m_tableWidget->setItem(row, 3, itemall);

    QProgressBar *bar = new QProgressBar;
    bar->setRange(0, 100);
    bar->setValue(percent);

    QString qss;
    if(percent < 50)
    {
        qss = "QProgressBar{text-align:center;border-width:0px;border-radius:0px;color:#000000;}"
              "QProgressBar::chunk{background:rgb(60, 140, 220);}";
    } else if(percent < 90)
    {
        qss = "QProgressBar{text-align:center;border-width:0px;border-radius:0px;color:#FFFFFF;}"
              "QProgressBar::chunk{background:rgb(60, 140, 220);}";
    } else
    {
        qss = "QProgressBar{text-align:center;border-width:0px;border-radius:0px;color:#FFFFFF;}"
              "QProgressBar::chunk{background:rgb(215, 19, 69);}";
    }

    bar->setStyleSheet(qss);
    m_tableWidget->setCellWidget(row, 4, bar);
}
