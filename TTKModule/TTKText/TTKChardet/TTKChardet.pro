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

win32:TARGET = ../../../../bin/$$TTKTinyTools/TTKChardet
unix:TARGET = ../../../lib/$$TTKTinyTools/TTKChardet

SOURCES += \
    main.cpp \
    checker.cpp \
    ascii.cpp \
    big5.cpp \
    gb18030.cpp \
    gbk.cpp \
    shiftjis.cpp \
    utf8.cpp \
    iso2022_jp.cpp \
    checkerhelper.cpp

HEADERS += \
    checker.h \
    iso2022_jp.h \
    ascii.h \
    big5.h \
    gb18030.h \
    gbk.h \
    shiftjis.h \
    utf8.h \
    checkerhelper.h
