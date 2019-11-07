#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waterwave.h"

#include <QTimer>
#include <QPainter>
#include <QFileDialog>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_waterWave = nullptr;
    m_ui->setupUi(this);

    connect(m_ui->openButton, SIGNAL(clicked(bool)), SLOT(openImage()));

    m_timer = new QTimer(this);
    m_timer->setInterval(20);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(renderImage()));
}

MainWindow::~MainWindow()
{
    delete m_timer;
    delete m_waterWave;
    delete m_ui;
}

void MainWindow::openImage()
{
    const QString &path = QFileDialog::getOpenFileName(this, "Please Image", "", "Images (*.png *.bmp *.jpg)");
    if(path.isEmpty())
    {
        return;
    }

    m_image.load(path);
    m_waterWave = new WaterWave((int*)(m_image.bits()), m_image.width(), m_image.height(), m_image.format());
}

void MainWindow::renderImage()
{
    m_waterWave->run();
    memcpy(m_image.bits(), (const uchar*)m_waterWave->pixels(), m_image.byteCount());
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    if(m_waterWave)
    {
        m_waterWave->setWaveSource(event->pos().x(), event->pos().y(), 40, 100);
        m_timer->start();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(m_image.isNull())
    {
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    painter.drawImage(0, 0, m_image);
}
