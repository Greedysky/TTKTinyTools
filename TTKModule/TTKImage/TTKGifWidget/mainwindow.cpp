#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ttkdesktopwrapper.h"

#include <QStyle>
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    init();

    connect(m_ui->btnStart, SIGNAL(clicked()), SLOT(record()));
    connect(m_ui->btnClose, SIGNAL(clicked()), SLOT(closeAll()));
    connect(m_ui->txtWidth, SIGNAL(editingFinished()), SLOT(resizeForm()));
    connect(m_ui->txtHeight, SIGNAL(editingFinished()), SLOT(resizeForm()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::init()
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    installEventFilter(this);

    m_borderWidth = 3;
    m_bgColor = QColor(34, 163, 169);

    m_fps = 10;
    m_ui->txtFps->setText(QString::number(m_fps));
    m_gifWriter = nullptr;

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(saveImage()));

    m_ui->btnClose->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));

    QStringList qss;
    qss.append("QLabel{color:#ffffff;}");
    qss.append("#btnClose,#btnIcon{border:none;border-radius:0px;}");
    qss.append("#btnClose:hover{background-color:#ff0000;}");
    qss.append("#btnClose{border-top-right-radius:5px;}");
    qss.append("#labTitle{font:bold 16px;}");
    qss.append("#labStatus{font:15px;}");
    setStyleSheet(qss.join(QString()));
}

int MainWindow::getBorderWidth() const
{
    return m_borderWidth;
}

QColor MainWindow::getBgColor() const
{
    return m_bgColor;
}

void MainWindow::saveImage()
{
    if(!m_gifWriter)
    {
        return;
    }

    const QPixmap &pix = TTKDesktopWrapper::grabWindow(x() + m_rectGif.x(), y() + m_rectGif.y(), m_rectGif.width(), m_rectGif.height());
#if !TTK_QT_VERSION_CHECK(5,0,0)
    const QImage &image = pix.toImage().convertToFormat(QImage::Format_ARGB32);
#else
    const QImage &image = pix.toImage().convertToFormat(QImage::Format_RGBA8888);
#endif

    m_gif.GifWriteFrame(m_gifWriter, image.bits(), m_rectGif.width(), m_rectGif.height(), m_fps);
}

void MainWindow::record()
{
    const QString &fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss.gif");

    if(m_ui->btnStart->text() == "开始")
    {
        if(m_gifWriter)
        {
            delete m_gifWriter;
            m_gifWriter = nullptr;
        }

        const int width = m_ui->txtWidth->text().toInt();
        const int height = m_ui->txtHeight->text().toInt();
        m_fps = m_ui->txtFps->text().toInt();

        m_gifWriter = new Gif::GifWriter;
        if(!m_gif.GifBegin(m_gifWriter, fileName.toLocal8Bit().data(), width, height, m_fps))
        {
            delete m_gifWriter;
            m_gifWriter = nullptr;
            return;
        }

        saveImage();

        m_timer->start(1000 / m_fps);
        m_ui->labStatus->setText("开始录制...");
        m_ui->btnStart->setText("停止");
    }
    else
    {
        if(!m_gifWriter)
        {
            return;
        }

        m_timer->stop();
        m_gif.GifEnd(m_gifWriter);

        delete m_gifWriter;
        m_gifWriter = nullptr;

        m_ui->labStatus->setText("录制完成");
        m_ui->btnStart->setText("开始");
    }
}

void MainWindow::closeAll()
{
    if(m_gifWriter)
    {
        delete m_gifWriter;
        m_gifWriter = nullptr;
    }

    exit(0);
}

void MainWindow::resizeForm()
{
    const int width = m_ui->txtWidth->text().toInt();
    const int height = m_ui->txtHeight->text().toInt();
    resize(width, height + m_ui->widgetTop->height() + m_ui->widgetBottom->height());
}

void MainWindow::setBorderWidth(int borderWidth)
{
    if(m_borderWidth != borderWidth)
    {
        m_borderWidth = borderWidth;
        update();
    }
}

void MainWindow::setBgColor(const QColor &color)
{
    if(m_bgColor != color)
    {
        m_bgColor = color;
        update();
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if(mouseEvent->type() == QEvent::MouseButtonPress)
    {
        if(mouseEvent->button() == Qt::LeftButton)
        {
            mousePressed = true;
            mousePoint = mouseEvent->globalPos() - this->pos();
            return true;
        }
    }
    else if(mouseEvent->type() == QEvent::MouseButtonRelease)
    {
        mousePressed = false;
        return true;
    }
    else if(mouseEvent->type() == QEvent::MouseMove)
    {
        if(mousePressed && (mouseEvent->buttons() & Qt::LeftButton))
        {
            move(mouseEvent->globalPos() - mousePoint);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_ui->txtWidth->setText(QString::number(m_ui->widgetMain->width()));
    m_ui->txtHeight->setText(QString::number(m_ui->widgetMain->height()));
    QDialog::resizeEvent(event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    const int width = m_ui->txtWidth->text().toInt();
    const int height = m_ui->txtHeight->text().toInt();
    m_rectGif = QRect(m_borderWidth, m_ui->widgetTop->height(), width - (m_borderWidth * 2), height);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_bgColor);
    painter.drawRoundedRect(rect(), 5, 5);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(m_rectGif, Qt::SolidPattern);
}
