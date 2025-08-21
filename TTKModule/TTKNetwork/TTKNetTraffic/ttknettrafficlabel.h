#ifndef TTKNETTRAFFICLABEL_H
#define TTKNETTRAFFICLABEL_H

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

#include <QLabel>
#include "ttkabstractthread.h"

class QProcess;

/*!
* @author Greedysky <greedysky@163.com>
*/
class TTKNetTraffic : public TTKAbstractThread
{
    Q_OBJECT
public:
    /*!
     * Object constructor.
     */
    explicit TTKNetTraffic(QObject *parent = nullptr);
    ~TTKNetTraffic();

    /*!
     * Set newtwork name.
     */
    void setNewtworkName(const QString &name);

    /*!
     * Get current newtwork name.
     */
    QString currentNewtworkName() const;
    /*!
     * Get newtwork names.
     */
    QStringList newtworkNames() const;

Q_SIGNALS:
    /*!
     * Send current upload and download speed data.
     */
    void networkData(ulong upload, ulong download);

private Q_SLOTS:
    /*!
     * Get output recieved data on linux network.
     */
    void outputRecieved();

private:
    /*!
     * Thread run now.
     */
    virtual void run() override final;

private:
    QString m_name;
    QProcess *m_process;

};

#endif // TTKNETTRAFFICLABEL_H
