#include "barragewidget.h"
#include "barragecore.h"
#include "barrageanimation.h"
#include <QFile>
#include <QLabel>

BarrageWidget::BarrageWidget(QObject *parent)
    : QObject(parent),
      m_parentClass(TTKObjectCast(QWidget*, parent)),
      m_barrageState(false),
      m_fontSize(15),
      m_backgroundColor(0, 0, 0)
{
    readBarrage();
}

BarrageWidget::~BarrageWidget()
{
    writeBarrage();
    deleteItems();
}

void BarrageWidget::start()
{
    if(m_barrageState)
    {
        for(int i = 0; i < m_labels.count(); ++i)
        {
            m_labels[i]->show();
            m_animations[i]->start();
        }
    }
}

void BarrageWidget::pause()
{
    if(m_barrageState)
    {
        for(int i = 0; i < m_labels.count(); ++i)
        {
            m_labels[i]->hide();
            m_animations[i]->pause();
        }
    }
}

void BarrageWidget::stop()
{
    for(int i = 0; i < m_labels.count(); ++i)
    {
        m_labels[i]->hide();
        m_animations[i]->stop();
    }
}

void BarrageWidget::barrageStateChanged(bool on)
{
    m_barrageState = on;
    if(m_barrageState && !m_barrageList.isEmpty())
    {
        deleteItems();
        createLabel();
        createAnimation();
        setLabelTextSize(m_fontSize);
        start();
    }
    else
    {
        stop();
    }
}

void BarrageWidget::setSize(const QSize &size)
{
    m_parentSize = size;
    for(BarrageAnimation *anima : qAsConst(m_animations))
    {
        anima->setSize(size);
    }
}

void BarrageWidget::setLabelBackground(const QColor &color)
{
    m_backgroundColor = color;
    for(QLabel *label : qAsConst(m_labels))
    {
        setLabelBackground(label);
    }
}

void BarrageWidget::setLabelTextSize(int size)
{
    m_fontSize = size;
    for(QLabel *label : qAsConst(m_labels))
    {
        setLabelTextSize(label);
    }
}

void BarrageWidget::addBarrage(const QString &string)
{
    BarrageCore::timeSRand();
    QLabel *label = new QLabel(m_parentClass);
    createLabel(label);
    createAnimation(label);
    setLabelBackground(label);
    setLabelTextSize(label);

    label->setText(string);
    m_barrageList << string;

    if(m_barrageState)
    {
        if(m_labels.count() == 1)
        {
            deleteItems();
            createLabel();
            createAnimation();
        }
        setLabelTextSize(m_fontSize);
        start();
    }
}

void BarrageWidget::deleteItems()
{
    qDeleteAll(m_labels);
    qDeleteAll(m_animations);
}

void BarrageWidget::createLabel()
{
    BarrageCore::timeSRand();
    for(const QString &str : qAsConst(m_barrageList))
    {
        Q_UNUSED(str);
        QLabel *label = new QLabel(m_parentClass);
        createLabel(label);
    }
}

void BarrageWidget::createLabel(QLabel *label)
{
    QString color = QString("QLabel{color:rgb(%1,%2,%3);}")
            .arg(BarrageCore::random(255)).arg(BarrageCore::random(255)).arg(BarrageCore::random(255));
    label->setStyleSheet(color);
    if(!m_barrageList.isEmpty())
    {
        label->setText(m_barrageList[BarrageCore::random(m_barrageList.count())]);
    }
    label->hide();
    m_labels << label;
}

void BarrageWidget::createAnimation()
{
    for(QLabel *label : qAsConst(m_labels))
    {
        createAnimation(label);
    }
}

void BarrageWidget::createAnimation(QLabel *label)
{
    BarrageAnimation *anim = new BarrageAnimation(label, "pos");
    anim->setSize(m_parentSize);
    m_animations << anim;
}

void BarrageWidget::setLabelBackground(QLabel *label)
{
    QString colorString = QString("QLabel{background-color:rgb(%1,%2,%3);}")
            .arg(m_backgroundColor.red()).arg(m_backgroundColor.green())
            .arg(m_backgroundColor.blue());
    label->setStyleSheet(label->styleSheet() + colorString);
}

void BarrageWidget::setLabelTextSize(QLabel *label)
{
    QFont font = label->font();
    font.setPointSize(m_fontSize);
    label->setFont(font);

    const QFontMetrics ftm(font);
    label->resize(QtFontWidth(ftm, label->text()), ftm.height());
}

void BarrageWidget::readBarrage()
{
    QFile file(BARRAGEPATH_AL);
    if(file.open(QIODevice::ReadOnly))
    {
        m_barrageList << QString(file.readAll()).split("\r\n");
        for(int i = m_barrageList.count() -1; i >= 0; --i)
        {
            if(m_barrageList[i].isEmpty())
            {
                m_barrageList.removeAt(i);
            }
        }
    }
    file.close();
}

void BarrageWidget::writeBarrage()
{
    QFile file(BARRAGEPATH_AL);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QByteArray array;
        for(const QString &var : qAsConst(m_barrageList))
        {
            array.append((var + '\n').toUtf8());
        }
        file.write(array);
    }
    file.close();
}
