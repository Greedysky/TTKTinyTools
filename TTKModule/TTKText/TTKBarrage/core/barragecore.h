#ifndef BARRAGECORE_H
#define BARRAGECORE_H

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

#include <QApplication>
#include <time.h>

#define BARRAGEPATH     "videobarrage"
#define BARRAGEPATH_AL  BarrageCore::getAppDir() + BARRAGEPATH

namespace BarrageCore
{
    static void timeSRand()
    {
        qsrand(time(nullptr));
    }

    static QString getAppDir()
    {
        QString path = QApplication::applicationDirPath();
#ifdef QT_DEBUG
        path.chop(5);
        return path;
#else
        return path + "/";
#endif
    }

///Menu
//////////////////////////////////////////////////////
    const QString MMenuStyle01 = " \
            QMenu {border: 1px solid gray; padding: 5px; }\
            QMenu::item {padding: 4px 25px 4px 30px;border: 1px solid transparent; }\
            QMenu::item:disabled {color: #666666;}\
            QMenu::item:selected { color: white; background: #BBBBBB;}\
            QMenu::separator {height: 1px;background: #BBBBBB;margin-top: 5px; margin-bottom: 5px;}";

    const QString MMenuStyle02 = MMenuStyle01 + " \
            QMenu { background-color: rgba(255, 255, 255, 235);}";

///Slider
//////////////////////////////////////////////////////
    const QString MSliderStyle01 = " \
            QSlider::groove:vertical {border: 1px solid #4A708B; \
            background: #C0C0C0;  width: 5px;  border-radius: 1px;\
            padding-left:-1px;padding-right:-1px;  padding-top:-1px;  padding-bottom:-1px;}  \
            QSlider::sub-page:vertical {background: #575757;border:1px solid #4A708B;border-radius: 2px;}\
            QSlider::add-page:vertical {  \
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,  \
            stop:0 #c4c4c4, stop:1 #B1B1B1);  \
            background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,  \
            stop: 0 #5DCCFF, stop: 1 #1874CD);  \
            border: 0px solid #777;  width: 10px;border-radius: 2px;}  \
            QSlider::handle:vertical{\
            background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, \
            fx:0.5, fy:0.5, stop:0.6 #45ADED,stop:0.778409 rgba(255, 255, 255, 255));\
            height: 11px;margin-left: -3px;margin-right: -3px;border-radius: 5px;}\
            QSlider::handle:vertical:disabled {background: #eee;border: 1px solid #aaa;border-radius: 4px;}";

    const QString MSliderStyle02 = "\
            QSlider::groove:horizontal{background:#C0C0C0; height:8px;}\
            QSlider::sub-page:horizontal{background:#F7F66C;}\
            QSlider::add-page:horizontal{background:#4E4E4E;}\
            QSlider::handle:horizontal{background:#FFFFFF; width:10px;}";

///ToolButton
//////////////////////////////////////////////////////
    const QString MToolButtonStyle01 = " \
            QToolButton{background-color:transparent;}";

    const QString MToolButtonStyle02 = MToolButtonStyle01 + " \
            QToolButton::menu-indicator{image:None;}";

///PushButton
//////////////////////////////////////////////////////
    const QString MPushButtonStyle01 = "\
            QPushButton{background-color:transparent;}";

    const QString MPushButtonStyle02 = MPushButtonStyle01 + "\
            QPushButton{border-none;}";

///LineEdit
//////////////////////////////////////////////////////
    const QString MLineEditStyle01 = " \
            QLineEdit{ border: 1px solid gray;} \
            QLineEdit::hover{ border: 1px solid #AAAAFF;}";

    const QString MLineEditStyle02 = " \
            QLineEdit{border-image: url(:/image/searchline); \
            font-size:15px; color:#333333;}";

}

#endif // BARRAGECORE_H
