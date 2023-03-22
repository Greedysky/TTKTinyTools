#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/***************************************************************************
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2023 Greedysky Studio

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
 ***************************************************************************/

#include <QImage>
#include "ttkglobaldefine.h"

class TTK_MODULE_EXPORT MainWindow
{
public:
    enum class Decode
    {
        Aztec = 1 << 1,
        CodaBar = 1 << 2,
        Code39 = 1 << 3,
        Code93 = 1 << 4,
        Code128 = 1 << 5,
        DataMatrix = 1 << 6,
        Ean8 = 1 << 7,
        Ean13 = 1 << 8,
        Itf = 1 << 9,
        MaxiCode = 1 << 10,
        Pdf417 = 1 << 11,
        QrCode = 1 << 12,
        Rss14 = 1 << 13,
        RssExpanded = 1 << 14,
        UpcA = 1 << 15,
        UpcE = 1 << 16,
        UpcEanExtension = 1 << 17
    };

    QString decodeImage(const int decode = TTKStaticCast(int, Decode::QrCode));
    QString decodeImage(const QImage &image, const int decode = TTKStaticCast(int, Decode::QrCode));

};

#endif // MAINWINDOW_H
