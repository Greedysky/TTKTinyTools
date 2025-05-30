#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/***************************************************************************
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2025 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QMainWindow>
#include <QFileInfoList>
#include "ttkmoduleexport.h"

namespace Ui {
class MainWindow;
}

class TTK_MODULE_EXPORT MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    void convert();
    void chooseImage();
    void sizeTypeChanged(int index);

private:
    Ui::MainWindow *m_ui;

    QString m_path;

};

#endif // MAINWINDOW_H
