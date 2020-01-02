#include "mainwindow.h"
#include "settingwidget.h"
#include "helper.h"

#include <QTimer>
#include <QResource>
#include <QBoxLayout>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_isShowtop = true;
    m_isShowcpu = false;
    m_isShowmem = false;

    m_lableNWS = new QLabel(this);
    m_lableNWS->setMinimumWidth(200);
    m_lableMem = new QLabel(this);
    m_lableMem->setMinimumWidth(200);
    m_lableCPU = new QLabel(this);
    m_lableCPU->setMinimumWidth(200);

    m_buttonNWS = new QPushButton(this);
    m_buttonNWS->setMaximumSize(20, 20);
    connect(m_buttonNWS, SIGNAL(clicked()), SLOT(showWindow()));

    m_buttonMem = new QPushButton(this);
    m_buttonMem->setMaximumSize(20, 20);
    m_buttonCPU = new QPushButton(this);
    m_buttonCPU->setMaximumSize(20, 20);

    m_lableCPU->setVisible(false);
    m_buttonCPU->setVisible(false);

    m_lableMem->setVisible(false);
    m_buttonMem->setVisible(false);

    QResource::registerResource("resource.qrc");
    QPixmap icon(":/qss/ubuntu.png");
    QPixmap iconmem(":/qss/mem.png");
    QPixmap iconcpu(":/qss/cpu.png");
    m_buttonNWS->setIcon(icon);
    m_buttonMem->setIcon(iconmem);
    m_buttonCPU->setIcon(iconcpu);

    QHBoxLayout *layoutsmallNWS = new QHBoxLayout;
    layoutsmallNWS->addWidget(m_buttonNWS);
    layoutsmallNWS->addWidget(m_lableNWS);

    QHBoxLayout *layoutsmallMem = new QHBoxLayout;
    layoutsmallMem->addWidget(m_buttonMem);
    layoutsmallMem->addWidget(m_lableMem);

    QHBoxLayout *layoutsmallCPU = new QHBoxLayout;
    layoutsmallCPU->addWidget(m_buttonCPU);
    layoutsmallCPU->addWidget(m_lableCPU);

    QVBoxLayout *layoutmid = new QVBoxLayout;
    layoutmid->addLayout(layoutsmallCPU);
    layoutmid->addLayout(layoutsmallMem);
    layoutmid->addLayout(layoutsmallNWS);

    m_helper = new Helper;
    QTimer *timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()), SLOT(refreshInfo()));

    m_setingWidget = nullptr;

    setLayout(layoutmid);
    move(200, 200);

    setAttribute(Qt::WA_TranslucentBackground, true);
    Qt::WindowFlags flags = 0;
    flags = Qt::Window;
    flags |=Qt::FramelessWindowHint;
    flags |= Qt::WindowStaysOnTopHint;

    setWindowFlags(flags);
    setStyleSheet("border-radius: 0px;");

    m_helper->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::refreshInfo()
{
    m_lableNWS->setText(m_helper->getNWS());
    m_lableMem->setText("MemUsage: " + m_helper->getMem() + "%");
    m_lableCPU->setText("CpuUsage: " + m_helper->getCPU() + "%");
}

void MainWindow::showWindow()
{
    if(!m_setingWidget)
    {
        m_setingWidget = new SettingWidget(m_isShowtop, m_isShowcpu, m_isShowmem, pos());
        connect(m_setingWidget, SIGNAL(showtop(int)), SLOT(showtop(int)));
        connect(m_setingWidget, SIGNAL(showcpu(int)), SLOT(showcpu(int)));
        connect(m_setingWidget, SIGNAL(showmem(int)), SLOT(showmem(int)));
    }
    m_setingWidget->show();
}

void MainWindow::showcpu(int value)
{
    update();
    if(value)
    {
        setFixedHeight(height() + 25);
        m_isShowcpu = true;
        m_lableCPU->setVisible(true);
        m_buttonCPU->setVisible(true);
    }
    else
    {
        setFixedHeight(height() - 25);
        m_isShowcpu = false;
        m_lableCPU->setVisible(false);
        m_buttonCPU->setVisible(false);
    }
}

void MainWindow::showmem(int value)
{
    if(value)
    {
        setFixedHeight(height() + 25);
        m_isShowmem = true;
        m_lableMem->setVisible(true);
        m_buttonMem->setVisible(true);
    }
    else
    {
        setFixedHeight(height() - 25);
        m_isShowmem = false;
        m_lableMem->setVisible(false);
        m_buttonMem->setVisible(false);
    }
}

void MainWindow::showtop(int value)
{
    Qt::WindowFlags flags = 0;
    if(value)
    {
        m_isShowtop = true;
        flags = Qt::Window;
        flags |= Qt::FramelessWindowHint;
        flags |= Qt::WindowStaysOnTopHint;
    }
    else
    {
        m_isShowtop = false;
        flags = Qt::Window;
        flags |= Qt::FramelessWindowHint;
    }
    setWindowFlags(flags);
    show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_dPos = event->globalPos() - pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - m_dPos);
}
