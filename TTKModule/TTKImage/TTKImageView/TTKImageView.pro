# =================================================
# * This file is part of the TTK Tiny Tools project
# * Copyright (C) 2015 - 2020 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# =================================================

include($$PWD/../../../TTKTinyTools.pri)

win32:TARGET = ../../../../bin/$$TTKTinyTools/TTKImageView
unix:TARGET = ../../../lib/$$TTKTinyTools/TTKImageView

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    imageview.cpp

HEADERS += \
    mainwindow.h \
    imageview.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    TTKImageView.qrc
