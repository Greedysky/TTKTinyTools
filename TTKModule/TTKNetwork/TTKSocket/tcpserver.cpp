#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{
    setMaxPendingConnections(10);
}

void TcpServer::sendData(int clientID, const QByteArray &data)
{
    for(TcpClient *client : qAsConst(m_clientList))
    {
        if(client->clientID() == clientID)
        {
            client->write(data);
            break;
        }
    }
}

void TcpServer::closeAllClient()
{
    for(TcpClient *client : qAsConst(m_clientList))
    {
        client->close();
    }
}

void TcpServer::incomingConnection(int handle)
{
    TcpClient *client = new TcpClient(handle, this);
    client->setSocketDescriptor(handle);

    connect(client, SIGNAL(clientReadData(ClientData,QByteArray)), SIGNAL(clientReadData(ClientData,QByteArray)));
    connect(client, SIGNAL(clientDisConnect(ClientData)), SLOT(clientDisConnectChanged(ClientData)));

    ClientData pair;
    pair.m_clientID = handle;
    pair.m_ip = client->peerAddress().toString();
    pair.m_port = client->peerPort();
    emit clientConnect(pair);

    m_clientList.append(client);
}

void TcpServer::clientDisConnectChanged(const ClientData &pair)
{
    for(TcpClient *client : qAsConst(m_clientList))
    {
        if(client->clientID() == pair.m_clientID)
        {
            m_clientList.removeAll(client);
            emit clientDisConnect(pair);
            break;
        }
    }
}
