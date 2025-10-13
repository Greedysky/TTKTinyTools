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

cmake_minimum_required(VERSION 3.18.0)

if(TTK_QT_VERSION VERSION_GREATER "4")
  add_subdirectory(TTKBarrage)
endif()

add_subdirectory(TTKCaseTransform)
add_subdirectory(TTKChardet)
add_subdirectory(TTKChinese2Pinyin)
add_subdirectory(TTKCodeCount)
add_subdirectory(TTKCodeLines)
add_subdirectory(TTKHashTransform)
add_subdirectory(TTKRandomPassword)
add_subdirectory(TTKRandomUuid)
add_subdirectory(TTKTimestampTransform)
add_subdirectory(TTKUrlEncode)
add_subdirectory(TTKUtf16Transform)
