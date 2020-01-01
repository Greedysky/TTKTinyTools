#ifndef HELPER_H
#define HELPER_H

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

class TTKNetTraffic;
class TTKCPUMemoryLabel;

/*!
* @author Greedysky <greedysky@163.com>
*/
class TTK_CORE_EXPORT Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = 0);
    virtual ~Helper();

    void start();

    QString getNWS() const;       //read the network speed
    QString getMem() const;       //read memory
    QString getCPU() const;           //read CPU state

private Q_SLOTS:
    void setData(ulong upload, ulong download);

private:
    TTKNetTraffic *m_traffic;
    QString m_nwsInfo;

    TTKCPUMemoryLabel *m_memery;
};

#endif // HELPER_H
