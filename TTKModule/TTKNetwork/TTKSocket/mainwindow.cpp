#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tcpServer = new TcpServer(this);
    m_tcpClient = new QTcpSocket(this);

    ui->serverPortEdit->setText("65000");
    ui->clientPortEdit->setText("65000");
    ui->clientServerIPEdit->setText("192.168.1.107");
    ui->serverSendButton->setEnabled(false);

    connect(m_tcpClient, SIGNAL(readyRead()), SLOT(readData()));
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(m_tcpClient, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), SLOT(readError(QAbstractSocket::SocketError)));
#else
    connect(m_tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(readError(QAbstractSocket::SocketError)));
#endif
    connect(m_tcpServer, SIGNAL(clientConnect(ClientData)), SLOT(clientConnect(ClientData)));
    connect(m_tcpServer, SIGNAL(clientDisConnect(ClientData)), SLOT(clientDisConnect(ClientData)));
    connect(m_tcpServer, SIGNAL(clientReadData(ClientData,QByteArray)), SLOT(clientReadData(ClientData,QByteArray)));

    connect(ui->serverListenButton, SIGNAL(clicked()), SLOT(listenButtonClicked()));
    connect(ui->serverConnectButton, SIGNAL(clicked()), SLOT(connectButtonClicked()));
    connect(ui->serverSendButton, SIGNAL(clicked()), SLOT(serverSendClicked()));
    connect(ui->clientSendButton, SIGNAL(clicked()), SLOT(clientSendClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listenButtonClicked()
{
    if(ui->serverListenButton->text() != tr("Stop"))
    {
        if(m_tcpServer->listen(QHostAddress::Any, ui->serverPortEdit->text().toInt()))
        {
            ui->serverListenButton->setText(tr("Stop"));
            ui->serverLogEdit->append(tr("Listen Success!"));
            ui->serverSendButton->setEnabled(true);
        }
    }
    else
    {
        m_tcpServer->closeAllClient();
        m_tcpServer->close();

        ui->serverListenButton->setText(tr("Listen"));
        ui->serverLogEdit->append(tr("Stop Listen!"));
        ui->serverSendButton->setEnabled(false);
    }
}

void MainWindow::connectButtonClicked()
{
    if(ui->serverConnectButton->text() != tr("Disconnect"))
    {
        m_tcpClient->connectToHost(ui->clientServerIPEdit->text(), ui->clientPortEdit->text().toInt());
        if(m_tcpClient->waitForConnected(1000))
        {
            ui->serverConnectButton->setText(tr("Disconnect"));
            ui->clientLogEdit->append(tr("Connect Success!"));
            ui->clientSendButton->setEnabled(true);
        }
    }
    else
    {
        m_tcpClient->disconnectFromHost();
        if(m_tcpClient->state() == QAbstractSocket::UnconnectedState || m_tcpClient->waitForDisconnected(1000))
        {
            ui->clientLogEdit->setText(tr("Connect"));
            ui->clientLogEdit->append(tr("Disconnect Success!"));
            ui->clientSendButton->setEnabled(true);
        }
    }
}

void MainWindow::clientReadData(const ClientData &pair, const QByteArray &data)
{
    if(!data.isEmpty())
    {
        ui->serverLogEdit->append(tr("Receive:%1 From:[ClientID:%2 IP:%3 Port:%4] Time:%5")
                                  .arg(QString(data)).arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)
                                  .arg(QTime::currentTime().toString("hh:mm:ss")));
    }
}

void MainWindow::clientConnect(const ClientData &pair)
{
    ui->serverLogEdit->append(tr("Client:[ClientID:%1 IP:%2 Port:%3] Login Time:%4")
                              .arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)
                              .arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->serverComboBox->addItem(tr("%1:%2:%3").arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port));
}

void MainWindow::clientDisConnect(const ClientData &pair)
{
    ui->serverLogEdit->append(tr("Client:[ClientID:%1 IP:%2 Port:%3] Logoff Time:%4")
                              .arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)
                              .arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->serverComboBox->removeItem(ui->serverComboBox->findText(tr("%1:%2:%3").arg(pair.m_clientID).arg(pair.m_ip).arg(pair.m_port)));
}

void MainWindow::readData()
{
    QByteArray buffer = m_tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        ui->clientLogEdit->append(tr("Receive:%1 Time:%2")
                                  .arg(QString(buffer)).arg(QTime::currentTime().toString("hh:mm:ss")));
    }
}

void MainWindow::readError(QAbstractSocket::SocketError)
{
    m_tcpClient->disconnectFromHost();
    ui->serverConnectButton->setText(tr("Disconnect"));
    ui->clientLogEdit->append(tr("Connect Error:%1").arg(m_tcpClient->errorString()));
}

void MainWindow::serverSendClicked()
{
    QString data = ui->serverTextEdit->toPlainText();
    if(data.isEmpty())
    {
        return;
    }

    QString info = ui->serverComboBox->currentText();
    int clientID = info.split(":")[0].toInt();
    m_tcpServer->sendData(clientID, data.toUtf8());
}

void MainWindow::clientSendClicked()
{
    QString data = ui->clientTextEdit->toPlainText();
    if(!data.isEmpty())
    {
        m_tcpClient->write(data.toUtf8());
    }
}
