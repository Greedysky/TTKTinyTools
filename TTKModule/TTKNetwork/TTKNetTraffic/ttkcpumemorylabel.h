#ifndef TTKCPUMEMORYLABEL_H
#define TTKCPUMEMORYLABEL_H

/***************************************************************************
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2022 Greedysky Studio

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
 ***************************************************************************/

#include <QTimer>
#include "ttkglobaldefine.h"

class QProcess;

/*!
* @author Greedysky <greedysky@163.com>
*/
class TTK_MODULE_EXPORT TTKCPUMemoryLabel : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(TTKCPUMemoryLabel)
public:
    explicit TTKCPUMemoryLabel(QObject *parent = nullptr);
    ~TTKCPUMemoryLabel();

    float cpuInfo() const;
    float memeryInfo() const;

public Q_SLOTS:
    void start(int interval);
    void stop();

private Q_SLOTS:
    void cpu();
    void memory();
    void readData();

private:
    int m_totalNew, m_idleNew, m_totalOld, m_idleOld;

    float m_cpuPercent;
    float m_memoryPercent;

    int m_memoryAll;
    int m_memoryUse;
    int m_memoryFree;

    QTimer *m_timerCPU;
    QTimer *m_timerMemory;
    QProcess *m_process;

};

#endif // TTKCPUMEMORYLABEL_H
