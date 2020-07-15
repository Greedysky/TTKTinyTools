#include "waterwave.h"
#include <cstring>

WaterWave::WaterWave(int* pixels, int width, int height)
{
    init(pixels, width, height);
    m_scale = 1;
}

WaterWave::WaterWave(int* pixels, int width, int height, float scale)
{
    init(pixels, width, height);
    m_scale = scale;
}

WaterWave::~WaterWave()
{
    if(m_orginPixels)
    {
        delete[] m_orginPixels;
    }

    if(m_newPixels)
    {
        delete[] m_newPixels;
    }

    if(m_buffer1)
    {
        delete[] m_buffer1;
    }

    if(m_buffer2)
    {
        delete[] m_buffer2;
    }

    if(m_sourcePower)
    {
        delete[] m_sourcePower;
    }

    if(m_sourcePosition)
    {
        delete[] m_sourcePosition;
    }
}

int* WaterWave::pixels()
{
    return m_newPixels;
}

void WaterWave::run()
{
    spreedRipple();
    renderRipple();
}

void WaterWave::setWaveSource(int x, int y, int radius, int depth)
{
    setWaveSourcePower(radius, depth);
    setWaveSourcePosition(x, y);
}

void WaterWave::setWaveSourcePower(int radius, int depth)
{
    m_sourceRadius = static_cast<int>(radius/m_scale);
    m_sourceDepth = depth;

    initSourcePower();
}

void WaterWave::setWaveSourcePosition(int x, int y)
{
    const int sourceX = static_cast<int>(x / m_scale);
    const int sourceY = static_cast<int>(y / m_scale);
    if((sourceX + m_sourceRadius) >= m_width || (sourceY + m_sourceRadius) >= m_height || (sourceX - m_sourceRadius) <= 0 || (sourceY - m_sourceRadius) <= 0)
    {
        return;
    }

    const int distance = (sourceY - m_sourceRadius) * m_width + sourceX - m_sourceRadius;
    const int size = ((m_sourceRadius << 1) + 1) * ((m_sourceRadius << 1) + 1);
    for(int i = 0; i < size; ++i)
    {
        m_buffer1[distance + m_sourcePosition[i]] = static_cast<short>(m_sourcePower[i]);
    }
}

void WaterWave::spreedRipple()
{
    const int length = m_width * (m_height -1);
    for(int i = m_width; i < length; ++i)
    {
        m_buffer2[i] = ((m_buffer1[i - 1] + m_buffer1[i - m_width] + m_buffer1[i + 1] + m_buffer1[i + m_width]) >> 1) - m_buffer2[i];
        m_buffer2[i] -= m_buffer2[i] >> m_powerRate;
    }

    short* temp = m_buffer1;
    m_buffer1 = m_buffer2;
    m_buffer2 = temp;
}

void WaterWave::renderRipple()
{
    int offset;
    int w = m_width;
    for(int y = 1; y < m_height - 1; ++y)
    {
        for(int x = 0; x < m_width; ++x, ++w)
        {
            offset = (m_width * (m_buffer1[w - m_width] - m_buffer1[w + m_width])) + (m_buffer1[w - 1] - m_buffer1[w + 1]);
            if(w + offset > 0 && w + offset < m_width * m_height)
            {
                m_newPixels[w] = m_orginPixels[w + offset];
            }
            else
            {
                m_newPixels[w] = m_orginPixels[w];
            }
        }
    }
}

void WaterWave::init(int* pixels, int width, int height)
{
    m_orginPixels = nullptr;
    m_newPixels = nullptr;
    m_buffer1 = nullptr;
    m_buffer2 = nullptr;
    m_sourcePower = nullptr;
    m_sourcePosition = nullptr;

    m_width = width;
    m_height = height;

    m_orginPixels = new int[width * height];
    memcpy(m_orginPixels, pixels, width * height * 4);

    m_newPixels = new int[width * height]{};
    memcpy(m_newPixels, pixels, width * height * sizeof(int));

    m_buffer1 = new short[width * height]{};
    m_buffer2 = new short[width * height]{};

    m_powerRate = 3;
}

void WaterWave::initSourcePower()
{
    const int value = m_sourceRadius * m_sourceRadius;
    const int diameter = (m_sourceRadius << 1) + 1;
    const int rate = m_sourceRadius / value;

    const int size = diameter * diameter;
    m_sourcePower = new int[size]{};
    m_sourcePosition = new int[size]{};

    for(int x = 0; x <= diameter; ++x)
    {
        for(int y = 0; y <= diameter; ++y)
        {
            const int distanceSquare = (m_sourceRadius - x) * (m_sourceRadius - x) + (m_sourceRadius - y) * (m_sourceRadius - y);
            if(distanceSquare <= value)
            {
                const int depth = m_sourceDepth - distanceSquare * rate;
                m_sourcePosition[y * diameter + x] = y * m_width + x;
                m_sourcePower[y * diameter + x] = depth;
            }
        }
    }
}
