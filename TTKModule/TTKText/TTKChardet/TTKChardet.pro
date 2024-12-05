# ***************************************************************************
# * This file is part of the TTK Tiny Tools project
# * Copyright (C) 2015 - 2025 Greedysky Studio
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

TARGET = TTKChardet

HEADERS += \
    $$PWD/checker.h \
    $$PWD/iso2022_jp.h \
    $$PWD/ascii.h \
    $$PWD/big5.h \
    $$PWD/gb18030.h \
    $$PWD/gbk.h \
    $$PWD/shiftjis.h \
    $$PWD/utf8.h \
    $$PWD/checkerhelper.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/checker.cpp \
    $$PWD/ascii.cpp \
    $$PWD/big5.cpp \
    $$PWD/gb18030.cpp \
    $$PWD/gbk.cpp \
    $$PWD/shiftjis.cpp \
    $$PWD/utf8.cpp \
    $$PWD/iso2022_jp.cpp \
    $$PWD/checkerhelper.cpp
