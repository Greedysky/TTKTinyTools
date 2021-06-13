#ifndef TCPCLIENT_H
#define TCPCLIENT_H

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

#include <QTcpSocket>
#include "ttkglobaldefine.h"

typedef struct TTK_MODULE_EXPORT ClientData
{
    int m_clientID;
    QString m_ip;
    int m_port;
}ClientData;

class TTK_MODULE_EXPORT TcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClient(int clientID, QObject *parent = nullptr);

    int clientID() const;

Q_SIGNALS:
    void clientReadData(const ClientData &pair, const QByteArray &data);
    void clientDisConnect(const ClientData &pair);

private Q_SLOTS:
    void readData();
    void disConnect();

private:
    int m_clientID;

};

#endif // TCPCLIENT_H
