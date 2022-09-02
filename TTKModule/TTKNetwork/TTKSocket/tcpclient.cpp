#include "tcpclient.h"

#include <QHostAddress>

TcpClient::TcpClient(int clientID, QObject *parent)
    : QTcpSocket(parent),
      m_clientID(clientID)
{
    connect(this, SIGNAL(readyRead()), SLOT(readData()));
    connect(this, SIGNAL(disconnected()), SLOT(disConnect()));
}

int TcpClient::clientID() const
{
    return m_clientID;
}

void TcpClient::readData()
{
    ClientData pair;
    pair.m_clientID = m_clientID;
    pair.m_ip = peerAddress().toString();
    pair.m_port = peerPort();
    emit clientReadData(pair, readAll());
}

void TcpClient::disConnect()
{
    ClientData pair;
    pair.m_clientID = m_clientID;
    pair.m_ip = peerAddress().toString();
    pair.m_port = peerPort();
    emit clientDisConnect(pair);
}
