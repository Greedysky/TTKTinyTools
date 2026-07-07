#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ttkdesktopscreen.h"

#include <QLabel>
#include <QTimer>

QLabel *waylandDesktop = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    setFixedSize(width(), height());
    TTKDesktopScreen::centerWidget(this);

    m_pixmap = TTKDesktopScreen::grabWindow();

    if(qgetenv("XDG_SESSION_TYPE") == "wayland")
    {
        waylandDesktop = new QLabel;
        waylandDesktop->setPixmap(m_pixmap);
        waylandDesktop->showFullScreen();
    }

    RenderValue();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::RenderValue()
{
    const int x = QCursor::pos().x();
    const int y = QCursor::pos().y();
    m_ui->txtXY->setText(QString("X:%1  Y:%2").arg(x).arg(y));

    QString decimal, hex;
    const QPixmap& pix = m_pixmap.copy(x, y, 2, 2);

    if(!pix.isNull())
    {
        const QImage &image = pix.toImage();
        if(!image.isNull() && image.valid(0, 0))
        {
            const QRgb rgb = image.pixel(0, 0);
            const int red = qRed(rgb);
            const int green = qGreen(rgb);
            const int blue= qBlue(rgb);

            decimal = QString("%1, %2, %3").arg(red).arg(green).arg(blue);
            hex = QString("#%1%2%3").arg(QString("%1").arg(red & 0xFF , 2, 16, QLatin1Char('0')),
                       QString("%1").arg(green & 0xFF, 2, 16, QLatin1Char('0')),
                       QString("%1").arg(blue & 0xFF, 2, 16, QLatin1Char('0'))).toUpper();
        }
    }

    m_ui->txtWeb->setText(hex);
    m_ui->txtRgb->setText(decimal);
    m_ui->labColor->setStyleSheet(QString("background-color:rgb(%1)").arg(decimal));

    TTK_SIGNLE_SHOT(RenderValue, TTK_SLOT);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    delete waylandDesktop;
}
