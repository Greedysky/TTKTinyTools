#ifndef BARRAGEEDIT_H
#define BARRAGEEDIT_H

/***************************************************************************
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2025 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QLineEdit>
#include "ttkmoduleexport.h"

class TTK_MODULE_EXPORT BarrageEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit BarrageEdit(QWidget *parent = nullptr);

    void addFilterText(const QString &text);

Q_SIGNALS:
    void enterFinished(const QString &text);

private:
    virtual void focusInEvent(QFocusEvent *event) override final;
    virtual void focusOutEvent(QFocusEvent *event) override final;
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    virtual void keyPressEvent(QKeyEvent *event) override final;
    virtual void keyReleaseEvent(QKeyEvent *event) override final;

    QString m_filterText;

};

#endif // BARRAGEEDIT_H
