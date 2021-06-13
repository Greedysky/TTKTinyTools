#ifndef BARRAGEWIDGET_H
#define BARRAGEWIDGET_H

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

class QLabel;
class BarrageAnimation;

class TTK_MODULE_EXPORT BarrageWidget : public QObject
{
    Q_OBJECT
public:
    explicit BarrageWidget(QObject *parent = nullptr);
    ~BarrageWidget();

    void start();
    void pause();
    void stop();

    void barrageStateChanged(bool on);
    void setSize(const QSize &size);

    void setLabelBackground(const QColor &color);
    void setLabelTextSize(int size);
    void addBarrage(const QString &string);

protected:
    void deleteItems();
    void createLabel();
    void createLabel(QLabel *label);
    void createAnimation();
    void createAnimation(QLabel *label);
    void setLabelBackground(QLabel *label);
    void setLabelTextSize(QLabel *label);
    void readBarrage();
    void writeBarrage();

    QWidget *m_parentClass;
    bool m_barrageState;
    QSize m_parentSize;
    int m_fontSize;
    QColor m_backgroundColor;
    QList<QLabel*> m_labels;
    QList<BarrageAnimation*> m_animations;
    QStringList m_barrageLists;

};

#endif // BARRAGEWIDGET_H
