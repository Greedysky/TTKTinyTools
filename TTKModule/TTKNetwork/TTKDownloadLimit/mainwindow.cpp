#include "mainwindow.h"
#include "ui_mainwindow.h"
#ifdef Q_CC_MSVC
#  define WIN32_LEAN_AND_MEAN
#  include <qt_windows.h>
#elif defined Q_OS_UNIX || defined Q_CC_GNU
#  include <unistd.h>
#endif
#include <QDir>

#define RESOURCE_PATH  QDir::tempPath() + "/download.tkx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_reply(nullptr),
      m_limitValue(0),
      m_hasReceived(0),
      m_currentReceived(0),
      m_totalSize(0)
{
    m_ui->setupUi(this);
    setFixedSize(433, 194);

    m_file = new QFile(RESOURCE_PATH, this);
    m_manager = new QNetworkAccessManager(this);

    connect(m_ui->downloadButton, SIGNAL(clicked(bool)), SLOT(startToDownload()));
    connect(m_ui->autoButton, SIGNAL(clicked(bool)), SLOT(autoDownloadPressed()));
    connect(m_ui->limitButton, SIGNAL(clicked(bool)), SLOT(limitDownloadPressed()));
    connect(m_ui->limitValueBox, SIGNAL(valueChanged(int)), SLOT(limitValueBoxChanged(int)));
    connect(&m_timer, SIGNAL(timeout()), SLOT(updateDownloadSpeed()));

    m_ui->autoButton->click();
}

MainWindow::~MainWindow()
{
    deleteAll();
    delete m_ui;
}

void MainWindow::startToRequest(const QUrl &url)
{
    m_reply = m_manager->get(QNetworkRequest(url));
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(readyRead()), SLOT(downLoadReadyRead()));
    connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), SLOT(downloadProgress(qint64,qint64)));
    QtNetworkErrorConnect(m_reply, this, replyError, TTK_SLOT);
}

void MainWindow::deleteAll()
{
    m_file->remove();
    delete m_file;
    m_file = nullptr;

    if(m_reply)
    {
        m_reply->deleteLater();
        m_reply = nullptr;
    }

    if(m_manager)
    {
        m_manager->deleteLater();
        m_manager = nullptr;
    }
//    deleteLater();
}

void MainWindow::startToDownload()
{
    if(m_ui->downloadButton->text() == "download")
    {
        const QString &url = m_ui->pathEdit->text().trimmed();
        if(!url.isEmpty())
        {
            if(m_file->open(QIODevice::WriteOnly))
            {
                startToRequest(QUrl(url));
                m_timer.start(1000);
            }
        }
        m_ui->downloadStatusLabel->setText("downLoading");
        m_ui->downloadButton->setText("stop");
    }
    else
    {
        m_timer.stop();
        m_ui->downloadButton->setText("download");
        if(m_reply)
        {
            m_reply->abort();
            m_reply->deleteLater();
            m_reply = nullptr;
        }
    }
}

void MainWindow::downLoadFinished()
{
    if(!m_file)
    {
        return;
    }

    m_file->flush();
    m_file->close();
    const QVariant &redirectionTarget = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(m_reply->error())
    {
        m_file->remove();
    }
    else if(!redirectionTarget.isNull())
    {
        m_reply->deleteLater();
        if(m_file->open(QIODevice::WriteOnly))
        {
            m_file->resize(0);
            startToRequest(m_reply->url().resolved(redirectionTarget.toUrl()));
        }
        return;
    }
    else
    {
        m_ui->downloadButton->setText("download");
        m_ui->downloadStatusLabel->setText("downLoad Finished");
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}

void MainWindow::downLoadReadyRead()
{
    if(m_file)
    {
        m_file->write(m_reply->readAll());
    }
}

void MainWindow::replyError(QNetworkReply::NetworkError)
{
    m_ui->downloadStatusLabel->setText("replyError -- download faild");
    m_ui->downloadButton->setText("download");
    if(m_reply)
    {
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}

void MainWindow::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_currentReceived = bytesReceived;
    m_totalSize = bytesTotal;

    m_ui->progressBar->setRange(0, m_totalSize);
    m_ui->progressBar->setValue(m_currentReceived);
}

void MainWindow::autoDownloadPressed()
{
    m_limitValue = 0;
    m_ui->limitValueBox->setEnabled(false);
}

void MainWindow::limitDownloadPressed()
{
    m_limitValue = m_ui->limitValueBox->text().toLongLong();
    m_ui->limitValueBox->setEnabled(true);
}

void MainWindow::limitValueBoxChanged(int value)
{
    m_limitValue = value;
}

void MainWindow::updateDownloadSpeed()
{
    const int delta = m_currentReceived - m_hasReceived;
    ///limit speed
    if(m_limitValue != 0 && delta > m_limitValue * TTK_SN_KB2B)
    {
#ifdef Q_CC_MSVC
        ::Sleep((TTK_DN_S2MS - m_limitValue * TTK_SN_KB2B * TTK_DN_S2MS / delta) * 1000);
#elif defined Q_OS_UNIX || defined Q_CC_GNU
        usleep((TTK_DN_S2MS - m_limitValue * TTK_SN_KB2B * TTK_DN_S2MS / delta) * 1000);
#endif
    }

    m_hasReceived = m_currentReceived;
    m_ui->downloadSpeed->setText(sizeStandardization(delta) + "/s");
    m_ui->restOfTime->setText(delta == 0 ? "99:99:99" : timeStandardization((m_totalSize - m_currentReceived) / delta + 1));
}

QString MainWindow::sizeStandardization(qint64 size)
{
    QString front, back;
    if(size / 1024 == 0)
    {
        front = QString::number(size);
        back = "00";
    }
    else if(size / 1024 / 1024 == 0 && size / 1024 > 0)
    {
        front = QString::number(size / 1024);
        back = QString::number(size % 1024).left(2).rightJustified(2, '0') + "KB";
    }
    else if(size / 1024 / 1024 / 1024 == 0 && size / 1024 / 1024 > 0)
    {
        front = QString::number(size / 1024 / 1024);
        back = QString::number(size % (1024 * 1024)).left(2).rightJustified(2, '0') + "M";
    }
    else if(size / 1024 / 1024 / 1024 > 0)
    {
        front = QString::number(size / 1024 / 1024 / 1024);
        back = QString::number(size % (1024 * 1024 * 1024)).left(2).rightJustified(2, '0') + "T";
    }
    else
    {
        return QString("--");
    }
    return QString("%1.%2").arg(front, back);
}

QString MainWindow::timeStandardization(qint64 time)
{
    const int h = time / 3600;
    const int m = (time % 3600) / 60;
    const int s = time % 60;
    return QString("%1:%2:%3").arg(QString::number(h).rightJustified(2, '0'),
                                   QString::number(m).rightJustified(2, '0'),
                                   QString::number(s).rightJustified(2, '0'));
}
