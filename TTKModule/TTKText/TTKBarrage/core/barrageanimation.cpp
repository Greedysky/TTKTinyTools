#include "barrageanimation.h"
#include "barragecore.h"

BarrageAnimation::BarrageAnimation(QObject *parent)
    : QPropertyAnimation(parent)
{
    initialize();
}

BarrageAnimation::BarrageAnimation(QObject *target, const QByteArray &propertyName, QObject *parent)
    : QPropertyAnimation(target, propertyName, parent)
{
    initialize();
}

void BarrageAnimation::animationFinished()
{
    setDuration(TTK::random(10000) + TTK_DN_S2MS);
    setSize(m_parentSize);
    start();
}

void BarrageAnimation::setSize(const QSize &size)
{
    m_parentSize = size;
    int randHeight = TTK::random(size.height());
    setStartValue(QPoint(0, randHeight));
    setEndValue(QPoint(size.width(), randHeight));
}

void BarrageAnimation::initialize()
{
    TTK::initRandom();
    setDuration(TTK::random(10000) + TTK_DN_S2MS);
    setEasingCurve(QEasingCurve::Linear);

    connect(this, SIGNAL(finished()), SLOT(animationFinished()));
}
