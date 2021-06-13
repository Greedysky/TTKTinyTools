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

#include <QFile>
#include <QLabel>
#include <QPushButton>
#include "ttkglobaldefine.h"

class Helper;

/*!
* @author Greedysky <greedysky@163.com>
*/
class TTK_MODULE_EXPORT MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private Q_SLOTS:
    void refreshInfo();
    void showWindow();
    void showcpu(int value);
    void showmem(int value);
    void showtop(int value);

private:
    QLabel *m_lableNWS, *m_lableMem, *m_lableCPU;
    QPushButton *m_buttonNWS, *m_buttonMem, *m_buttonCPU;
    Helper *m_helper;
    QWidget *m_setingWidget;

    QPoint m_dPos;
    bool m_isShowtop, m_isShowcpu, m_isShowmem;

};

#endif // MAINWINDOW_H
