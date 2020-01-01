#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

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

class TTK_CORE_EXPORT GaussianBlur
{
public:
    GaussianBlur();

    void gaussBlur(QImage &img, int radius);

private:
    void gaussBlur1(int* pix, int w, int h, int radius);
    void gaussBlur2(int* pix, int w, int h, int radius);
    void boxBlurH(int* srcPix, int* destPix, int w, int h, int radius);
    void boxBlurV(int* srcPix, int* destPix, int w, int h, int radius);
    void boxBlur(int* srcPix, int* destPix, int w, int h, int r);
    void boxesForGauss(float sigma, int* size, int n);

};

#endif // GAUSSIANBLUR_H
