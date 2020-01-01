#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "gif.h"
#include <QDialog>
#include "ttkglobal.h"
#include "ttkglobaldefine.h"

namespace Ui {
class MainWindow;
}

class TTK_CORE_EXPORT MainWindow : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int m_borderWidth READ getBorderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor m_bgColor READ getBgColor WRITE setBgColor)
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();
    int getBorderWidth() const;
    QColor getBgColor() const;

private Q_SLOTS:
    void saveImage();
    void record();
    void closeAll();
    void resizeForm();

public Q_SLOTS:
    void setBorderWidth(int borderWidth);
    void setBgColor(const QColor &color);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *m_ui;

    int m_borderWidth;
    QColor m_bgColor;

    uint m_fps;
    QRect m_rectGif;
    QTimer *m_timer;

    Gif m_gif;
    Gif::GifWriter *m_gifWriter;

};

#endif // MAINWINDOW_H
