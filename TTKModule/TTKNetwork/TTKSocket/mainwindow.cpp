#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_tcpServer = new TcpServer(this);
    m_tcpClient = new QTcpSocket(this);

    m_ui->serverPortEdit->setText("65000");
    m_ui->clientPortEdit->setText("65000");
    m_ui->clientServerIPEdit->setText("192.168.1.107");
    m_ui->serverSendButton->setEnabled(false);

    connect(m_tcpClient, SIGNAL(readyRead()), SLOT(readData()));
    QtSocketErrorConnect(m_tcpClient, this, readError, TTK_SLOT);

    connect(m_tcpServer, SIGNAL(clientConnect(ClientData)), SLOT(clientConnect(ClientData)));
    connect(m_tcpServer, SIGNAL(clientDisConnect(ClientData)), SLOT(clientDisConnect(ClientData)));
    connect(m_tcpServer, SIGNAL(clientReadData(ClientData,QByteArray)), SLOT(clientReadData(ClientData,QByteArray)));

    connect(m_ui->serverListenButton, SIGNAL(clicked()), SLOT(listenButtonClicked()));
    connect(m_ui->serverConnectButton, SIGNAL(clicked()), SLOT(connectButtonClicked()));
    connect(m_ui->serverSendButton, SIGNAL(clicked()), SLOT(serverSendClicked()));
    connect(m_ui->clientSendButton, SIGNAL(clicked()), SLOT(clientSendClicked()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::listenButtonClicked()
{
    if(m_ui->serverListenButton->text() != tr("Stop"))
    {
        if(m_tcpServer->listen(QHostAddress::Any, m_ui->serverPortEdit->text().toInt()))
        {
            m_ui->serverListenButton->setText(tr("Stop"));
            m_ui->serverLogEdit->append(tr("Listen Success"));
            m_ui->serverSendButton->setEnabled(true);
        }
    }
    else
    {
        m_tcpServer->closeAllClient();
        m_tcpServer->close();

        m_ui->serverListenButton->setText(tr("Listen"));
        m_ui->serverLogEdit->append(tr("Stop Listen"));
        m_ui->serverSendButton->setEnabled(false);
    }
}

void MainWindow::connectButtonClicked()
{
    if(m_ui->serverConnectButton->text() != tr("Disconnect"))
    {
        m_tcpClient->connectToHost(m_ui->clientServerIPEdit->text(), m_ui->clientPortEdit->text().toInt());
        if(m_tcpClient->waitForConnected(1000))
        {
            m_ui->serverConnectButton->setText(tr("Disconnect"));
            m_ui->clientLogEdit->append(tr("Connect Success"));
            m_ui->clientSendButton->setEnabled(true);
        }
    }
    else
    {
        m_tcpClient->disconnectFromHost();
        if(m_tcpClient->state() == QAbstractSocket::UnconnectedState || m_tcpClient->waitForDisconnected(1000))
        {
            m_ui->clientLogEdit->setText(tr("Connect"));
            m_ui->clientLogEdit->append(tr("Disconnect Success"));
            m_ui->clientSendButton->setEnabled(true);
        }
    }
}

void MainWindow::clientReadData(const ClientData &pair, const QByteArray &data)
{
    if(!data.isEmpty())
    {
        m_ui->serverLogEdit->append(tr("Receive:%1 From:[ClientID:%2 IP:%3 Port:%4] Time:%5")
                                  .arg(QString(data)).arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)
                                  .arg(QTime::currentTime().toString(TTK_TIMEZ_FORMAT)));
    }
}

void MainWindow::clientConnect(const ClientData &pair)
{
    m_ui->serverLogEdit->append(tr("Client:[ClientID:%1 IP:%2 Port:%3] Login Time:%4")
                              .arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)
                              .arg(QTime::currentTime().toString(TTK_TIMEZ_FORMAT)));
    m_ui->serverComboBox->addItem(tr("%1:%2:%3").arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port));
}

void MainWindow::clientDisConnect(const ClientData &pair)
{
    m_ui->serverLogEdit->append(tr("Client:[ClientID:%1 IP:%2 Port:%3] Logoff Time:%4")
                              .arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)
                              .arg(QTime::currentTime().toString(TTK_TIMEZ_FORMAT)));
    m_ui->serverComboBox->removeItem(m_ui->serverComboBox->findText(tr("%1:%2:%3").arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)));
}

void MainWindow::readData()
{
    const QByteArray &buffer = m_tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        m_ui->clientLogEdit->append(tr("Receive:%1 Time:%2")
                                  .arg(QString(buffer)).arg(QTime::currentTime().toString(TTK_TIMEZ_FORMAT)));
    }
}

void MainWindow::readError(QAbstractSocket::SocketError)
{
    m_tcpClient->disconnectFromHost();
    m_ui->serverConnectButton->setText(tr("Disconnect"));
    m_ui->clientLogEdit->append(tr("Connect Error:%1").arg(m_tcpClient->errorString()));
}

void MainWindow::serverSendClicked()
{
    const QString &data = m_ui->serverTextEdit->toPlainText();
    if(data.isEmpty())
    {
        return;
    }

    const QString &info = m_ui->serverComboBox->currentText();
    const int clientID = info.split(":")[0].toInt();
    m_tcpServer->sendData(clientID, data.toUtf8());
}

void MainWindow::clientSendClicked()
{
    const QString &data = m_ui->clientTextEdit->toPlainText();
    if(!data.isEmpty())
    {
        m_tcpClient->write(data.toUtf8());
    }
}
