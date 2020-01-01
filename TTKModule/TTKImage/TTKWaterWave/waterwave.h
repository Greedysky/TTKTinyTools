#ifndef WATERWAVE_H
#define WATERWAVE_H

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

#include "ttkglobaldefine.h"

class TTK_CORE_EXPORT WaterWave
{
public:
    WaterWave(int* pixels, int width, int height, int pixelFormat);
    WaterWave(int* pixels, int width, int height, int pixelFormat, float scale);
    ~WaterWave();

    int* pixels();
    void run();

    void setWaveSource(int x, int y, int radius, int depth);

private:
    void setWaveSourcePower(int radius, int depth);
    void setWaveSourcePosition(int x, int y);

    void spreedRipple();
    void renderRipple();

    void init(int* pixels, int width, int height, int pixelFormat);
    void initSourcePower();

private:
    int* m_orginPixels;
    int* m_newPixels;
    short* m_buffer1;
    short* m_buffer2;
    int* m_sourcePower;
    int* m_sourcePosition;

    int m_width;
    int m_height;
    int m_length;
    int m_pixelFormat;

    int m_powerRate;
    float m_scale;

    int m_sourceRadius;
    int m_sourceDepth;

};

#endif //WATERWAVE_H
