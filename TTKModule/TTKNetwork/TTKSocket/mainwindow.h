#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "tcpserver.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TTK_CORE_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    void listenButtonClicked();
    void connectButtonClicked();
    void clientReadData(const ClientData &pair, const QByteArray &data);
    void clientConnect(const ClientData &pair);
    void clientDisConnect(const ClientData &pair);
    void readData();
    void readError(QAbstractSocket::SocketError error);
    void serverSendClicked();
    void clientSendClicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcpClient;
    TcpServer *m_tcpServer;

};

#endif // MAINWINDOW_H
