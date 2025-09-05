#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ttkdesktopscreen.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    const QRect &rect = TTKDesktopScreen::currentGeometry();
    move(rect.x() + (rect.width() - width()) / 2, rect.y() + (rect.height() - height()) / 2);
    setFixedSize(width(), height());

    ShowColorValue();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::ShowColorValue()
{
    const int x = QCursor::pos().x();
    const int y = QCursor::pos().y();
    m_ui->txtXY->setText(QString("X:%1  Y:%2").arg(x).arg(y));

    QString strDecimal, strHex;
    const QPixmap &pixmap = TTKDesktopScreen::grabWindow(x, y, 2, 2);
    if(!pixmap.isNull())
    {
        const QImage &image = pixmap.toImage();
        if(!image.isNull() && image.valid(0, 0))
        {
            const QRgb rgb = image.pixel(0, 0);
            const int red = qRed(rgb);
            const int green = qGreen(rgb);
            const int blue= qBlue(rgb);

            strDecimal = QString("%1, %2, %3")
                    .arg(red)
                    .arg(green)
                    .arg(blue);
            strHex = QString("#%1%2%3")
                    .arg(QString("%1").arg(red & 0xFF , 2, 16, QLatin1Char('0')),
                         QString("%1").arg(green & 0xFF, 2, 16, QLatin1Char('0')),
                         QString("%1").arg(blue & 0xFF, 2, 16, QLatin1Char('0'))).toUpper();
        }
    }

    m_ui->labColor->setStyleSheet(QString("background-color:rgb(%1);").arg(strDecimal));
    m_ui->txtRgb->setText(strDecimal);
    m_ui->txtWeb->setText(strHex);

    TTK_SIGNLE_SHOT(ShowColorValue, TTK_SLOT);
}
