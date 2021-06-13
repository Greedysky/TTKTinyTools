#ifndef SHOWDEVICESIZE_H
#define SHOWDEVICESIZE_H

/* =================================================
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2021 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include <QObject>
#include <QMutex>
#include "ttkglobaldefine.h"

class QTableWidget;
class QProcess;

class TTK_MODULE_EXPORT ShowDeviceSize : public QObject
{
    Q_OBJECT
public:
    explicit ShowDeviceSize(QObject *parent = nullptr);
    static ShowDeviceSize *instance()
    {
        static QMutex mutex;
        if(!m_instance)
        {
            QMutexLocker locker(&mutex);
            if(!m_instance)
            {
                m_instance = new ShowDeviceSize;
            }
        }
        return m_instance;
    }

    void setTableWidget(QTableWidget *table);
    void load();

private Q_SLOTS:
    void readData();
    void checkSize(const QString &result, const QString &name);
    void insertSize(const QString &name, const QString &use, const QString &free, const QString &all, int percent);

private:
    static ShowDeviceSize *m_instance;
    QTableWidget *m_tableWidget;
    QProcess *m_process;

};

#endif // SHOWDEVICESIZE_H
