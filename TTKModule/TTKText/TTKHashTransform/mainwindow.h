#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "ttkglobaldefine.h"

class TTK_MODULE_EXPORT MainWindow
{
public:
    inline QString source() const { return m_source; }
    inline QString target() const { return m_target; }

    void setSource(const QString &string);
    void resetSource();
    void resetTarget();
    void clear();
    void cut();
    void calculateToBase64();
    void calculateFromBase64();
    void calculateMD4();
    void calculateMD5();
    void calculateSha1();
#if TTK_QT_VERSION_CHECK(5,0,0)
    void calculateSha224();
    void calculateSha256();
    void calculateSha384();
    void calculateSha512();
    void calculateSha3_224();
    void calculateSha3_256();
    void calculateSha3_384();
    void calculateSha3_512();
#endif

private:
    QString m_source;
    QString m_target;
};

#endif // MAINWINDOW_H
