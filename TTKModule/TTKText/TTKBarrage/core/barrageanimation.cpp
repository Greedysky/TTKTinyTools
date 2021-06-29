#include "barrageanimation.h"
#include "barragecore.h"

BarrageAnimation::BarrageAnimation(QObject *parent)
    : QPropertyAnimation(parent)
{
    init();
}

BarrageAnimation::BarrageAnimation(QObject *target, const QByteArray &propertyName, QObject *parent)
    : QPropertyAnimation(target, propertyName, parent)
{
    init();
}

void BarrageAnimation::animationFinished()
{
    setDuration(BarrageCore::random(10000) + 1000);
    setSize(m_parentSize);
    start();
}

void BarrageAnimation::setSize(const QSize &size)
{
    m_parentSize = size;
    int randHeight = BarrageCore::random(size.height());
    setStartValue(QPoint(0, randHeight));
    setEndValue(QPoint(size.width(), randHeight));
}

void BarrageAnimation::init()
{
    BarrageCore::timeSRand();
    setDuration(BarrageCore::random(10000) + 1000);
    setEasingCurve(QEasingCurve::Linear);

    connect(this, SIGNAL(finished()), SLOT(animationFinished()));
}
