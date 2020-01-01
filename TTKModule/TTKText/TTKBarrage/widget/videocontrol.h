#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

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

#include <QMenu>
#include <QWidget>
#include "ttkglobaldefine.h"

class QLabel;
class QSlider;
class QToolButton;
class QPushButton;

class TTK_CORE_EXPORT VideoControl : public QWidget
{
    Q_OBJECT
public:
    explicit VideoControl(QWidget *parent = nullptr);
    ~VideoControl();

    void setValue(qint64 position) const;
    void durationChanged(qint64 duration) const;
    void setButtonStyle(bool style) const;
    void setFixedSize(int w, int h);

Q_SIGNALS:
    void sliderValueChanged(int value);
    void mediaChanged(const QString &data);

    void addBarrageChanged(const QString &string);
    void pushBarrageChanged(bool on);
    void barrageSizeButtonChanged(int size);
    void barrageColorButtonChanged(const QColor &color);

public Q_SLOTS:
    void sliderReleased();
    void openFileDialog();

    void pushBarrageClicked();
    void barrageSizeButtonClicked(int index);
    void barrageColorButtonClicked(int index);

protected:
    QWidget* createBarrageWidget();
    QPushButton* createBarrageSizeButton(int index);
    QPushButton* createBarrageColorButton(int index);

    QMenu m_popupVolumn, m_popupBarrage;
    QSlider *m_timeSlider, *m_volumnSlider;
    QToolButton *m_menuButton, *m_volumnButton;
    QPushButton *m_playButton, *m_pushBarrage;
    bool m_pushBarrageOn;

};

#endif // VIDEOCONTROL_H
