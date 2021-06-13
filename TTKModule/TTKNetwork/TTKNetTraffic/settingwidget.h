#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

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

#include <QCheckBox>
#include "ttkglobaldefine.h"

/*!
* @author Greedysky <greedysky@163.com>
*/
class TTK_MODULE_EXPORT SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(bool top, bool cpu, bool mem, const QPoint &pos, QWidget *parent = 0);

Q_SIGNALS:
    void showtop(int value);
    void showcpu(int value);
    void showmem(int value);

public Q_SLOTS:
    void windowQuit();

private:
    QCheckBox *m_topBox;
    QCheckBox *m_cpubox;
    QCheckBox *m_membox;
};

#endif // SETTINGWIDGET_H
