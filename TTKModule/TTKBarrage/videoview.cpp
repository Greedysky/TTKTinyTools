#include "videoview.h"
#include "videocontrol.h"
#include "barragewidget.h"

#include <QVideoWidget>
#include <QBoxLayout>

VideoView::VideoView(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(700, 500);

    m_player = new QMediaPlayer(this);
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(stateChanged(QMediaPlayer::State)));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(m_player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));

    m_videoWidget = new QVideoWidget(this);

    m_control = new VideoControl(this);
    connect(m_control, SIGNAL(mediaChanged(QString)), SLOT(mediaChanged(QString)));
    connect(m_control, SIGNAL(sliderValueChanged(int)), SLOT(setPosition(int)));
    connect(m_control, SIGNAL(addBarrageChanged(QString)), SLOT(addBarrageChanged(QString)));
    connect(m_control, SIGNAL(pushBarrageChanged(bool)), SLOT(pushBarrageChanged(bool)));
    connect(m_control, SIGNAL(barrageSizeButtonChanged(int)), SLOT(barrageSizeButtonChanged(int)));
    connect(m_control, SIGNAL(barrageColorButtonChanged(QColor)), SLOT(barrageColorButtonChanged(QColor)));
    m_control->setGeometry(15, 430, 670, 50);
    m_control->hide();

    m_barrageCore = new BarrageWidget(this);
    m_barrageCore->setSize(QSize(650, 380));
    m_player->setVideoOutput(m_videoWidget);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_videoWidget);
    setLayout(layout);

}

VideoView::~VideoView()
{
    delete m_barrageCore;
    delete m_player;
    delete m_videoWidget;
    delete m_control;
}

void VideoView::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    m_control->show();
}

void VideoView::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    m_control->hide();
}

void VideoView::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}

void VideoView::play()
{
    switch(m_player->state())
    {
        case QMediaPlayer::PlayingState:
            m_player->pause();
            break;
        case QMediaPlayer::PausedState:
            m_player->play();
            break;
        case QMediaPlayer::StoppedState:
            m_player->stop();
            break;
        default: break;
    }
}

void VideoView::stateChanged(QMediaPlayer::State state)
{
    switch(state)
    {
        case QMediaPlayer::PlayingState:
            m_control->setButtonStyle(false);
            m_barrageCore->start();
            break;
        case QMediaPlayer::PausedState:
            m_control->setButtonStyle(true);
            m_barrageCore->pause();
            break;
        case QMediaPlayer::StoppedState:
            m_control->setButtonStyle(true);
            m_barrageCore->pause();
            break;
        default: break;
    }
}

void VideoView::positionChanged(qint64 position)
{
    m_control->setValue(position);
}

void VideoView::durationChanged(qint64 duration)
{
    m_control->durationChanged(duration);
}

void VideoView::setPosition(int position)
{
    m_player->setPosition(position);
}

void VideoView::volumnChanged(int volumn)
{
    m_player->setVolume(volumn);
}

void VideoView::mediaChanged(const QString &data)
{
    m_player->setMedia(QUrl(data));
    m_player->play();
}

void VideoView::addBarrageChanged(const QString &string)
{
    m_barrageCore->addBarrage(string);
}

void VideoView::pushBarrageChanged(bool on)
{
    m_barrageCore->barrageStateChanged(on);
}

void VideoView::barrageSizeButtonChanged(int size)
{
    m_barrageCore->setLabelTextSize(size);
}

void VideoView::barrageColorButtonChanged(const QColor &color)
{
    m_barrageCore->setLabelBackground(color);
}
