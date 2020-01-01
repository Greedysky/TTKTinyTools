#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

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

#include <QWidget>
#include <QMediaPlayer>

class QVideoWidget;
class VideoControl;
class BarrageWidget;

class VideoView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoView(QWidget *parent = nullptr);
    ~VideoView();

public Q_SLOTS:
    void play();

private Q_SLOTS:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void volumnChanged(int volumn);
    void mediaChanged(const QString &data);
    void stateChanged(QMediaPlayer::State state);

    void addBarrageChanged(const QString &string);
    void pushBarrageChanged(bool on);
    void barrageSizeButtonChanged(int size);
    void barrageColorButtonChanged(const QColor &color);

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

    QMediaPlayer *m_player;
    QVideoWidget *m_videoWidget;
    VideoControl *m_control;
    BarrageWidget *m_barrageCore;

};

#endif // VIDEOVIEW_H
