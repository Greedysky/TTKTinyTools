# ***************************************************************************
# * This file is part of the TTK Tiny Tools project
# * Copyright (C) 2015 - 2024 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU Lesser General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU Lesser General Public License for more details.
#
# * You should have received a copy of the GNU Lesser General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************

include($$PWD/../../../TTKTinyTools.pri)

TARGET = TTKBarrage

equals(QT_MAJOR_VERSION, 4){
    QT += multimedia
}

equals(QT_MAJOR_VERSION, 6):lessThan(QT_MINOR_VERSION, 2){
    message(Qt6.0.x and 6.1.x not support multimediawidgets)
}else{
    greaterThan(QT_MAJOR_VERSION, 4){
        QT += multimediawidgets
    }
}

TRANSLATIONS += $$PWD/cn.ts

INCLUDEPATH += \
    $$PWD/ \
    $$PWD/core \
    $$PWD/widget

HEADERS += \
    $$PWD/widget/barragewidget.h \
    $$PWD/widget/videocontrol.h \
    $$PWD/widget/barrageedit.h \
    $$PWD/core/barrageanimation.h \
    $$PWD/core/barragecore.h \
    $$PWD/videoview.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/widget/barragewidget.cpp \
    $$PWD/widget/videocontrol.cpp \
    $$PWD/widget/barrageedit.cpp \
    $$PWD/core/barrageanimation.cpp \
    $$PWD/videoview.cpp

RESOURCES += $$PWD/$${TARGET}.qrc
