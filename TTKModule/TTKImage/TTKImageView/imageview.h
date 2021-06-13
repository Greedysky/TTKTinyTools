#ifndef TTKIMAGEVIEW_H
#define TTKIMAGEVIEW_H

/* =================================================
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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
#include "ttkglobaldefine.h"

class QToolButton;

class TTK_MODULE_EXPORT ImageIndex : public QWidget
{
    Q_OBJECT
public:
    ImageIndex(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    void drawBg(QPainter *painter);
    void drawText(QPainter *painter);

public Q_SLOTS:
    void setTotalNum(int totalNum);
    void setCurrentIndex(int currentIndex);

private:
    int m_totalNum;
    int m_currentIndex;

};


class TTK_MODULE_EXPORT ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = nullptr);
    ~ImageView();

Q_SIGNALS:
    void totalNumChanged(int totalNum);
    void currentIndexChanged(int currentIndex);

private Q_SLOTS:
    void calcGeometry();
    void fading();

public Q_SLOTS:
    void load();
    void load(const QString &strFolder);

    void clear();

    void setBottomSpace(int bottomSpace);
    void setButtonSpace(int buttonSpace);

    void setIcoSize(const QSize &icoSize);

    void setFill(bool fill);
    void setFade(bool fade);
    void setKeyMove(bool keyMove);

    void moveFirst();
    void moveLast();
    void movePrevious();
    void moveNext();
    void moveToPage(int index);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
    void drawBg(QPainter *painter);
    void drawImage(QPainter *painter);

private:
    int m_bottomSpace;
    int m_buttonSpace;
    QSize m_icoSize;

    bool m_fill;
    bool m_fade;
    bool m_keyMove;

    QToolButton *m_preButton;
    QToolButton *m_nextButton;

    QStringList m_imageNames;
    int m_currentIndex;
    QImage m_currentImage;

    ImageIndex *m_imageIndex;

    int m_totalNum;
    double m_opacity;
    QTimer *m_timer;

};

#endif // TTKIMAGEVIEW_H
