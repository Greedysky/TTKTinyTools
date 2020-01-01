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

#include <QImage>
#include "ttkglobaldefine.h"

class TTK_CORE_EXPORT MainWindow
{
public:
    enum DecodeType
    {
        DecodeAztecType = 1 << 1,
        DecodeCodaBarType = 1 << 2,
        DecodeCode39Type = 1 << 3,
        DecodeCode93Type = 1 << 4,
        DecodeCode128Type = 1 << 5,
        DecodeDataMatrixType = 1 << 6,
        DecodeEan8Type = 1 << 7,
        DecodeEan13Type = 1 << 8,
        DecodeItfType = 1 << 9,
        DecodeMaxiCodeType = 1 << 10,
        DecodePdf417Type = 1 << 11,
        DecodeQrCodeType = 1 << 12,
        DecodeRss14Type = 1 << 13,
        DecodeRssExpandedType = 1 << 14,
        DecodeUpcAType = 1 << 15,
        DecodeUpcEType = 1 << 16,
        DecodeUpcEanExtensionType = 1 << 17
    };

    QString decodeImage(const int decodeType = static_cast<int>(DecodeQrCodeType));
    QString decodeImage(const QImage &image, const int decodeType = static_cast<int>(DecodeQrCodeType));

};

#endif // MAINWINDOW_H
