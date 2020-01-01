#ifndef SHOWCPUMEMORY_H
#define SHOWCPUMEMORY_H

/* =================================================
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2020 Greedysky Studio

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
#include "ttkglobaldefine.h"

class QLabel;
class QTimer;
class QProcess;

class TTK_CORE_EXPORT ShowCPUMemory : public QObject
{
    Q_OBJECT
public:
    explicit ShowCPUMemory(QObject *parent = nullptr);

    void setLab(QLabel *label);
    void start(int interval);
    void stop();

private Q_SLOTS:
    void getCPU();
    void getMemory();
    void readData();

private:
    int m_totalNew, m_idleNew, m_totalOld, m_idleOld;
    int m_cpuPercent;

    int m_memoryPercent;
    int m_memoryAll;
    int m_memoryUse;
    int m_memoryFree;

    QTimer *m_timerCPU;
    QTimer *m_timerMemory;
    QLabel *m_labCPUMemory;
    QProcess *m_process;

};

#endif // SHOWCPUMEMORY_H
