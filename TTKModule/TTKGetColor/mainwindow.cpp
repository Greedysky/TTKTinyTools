#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    QDesktopWidget *desktop = QApplication::desktop();

    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    move((desktop->width() - width())/2, (desktop->height() - height())/2);
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
#ifndef TTK_GREATER_NEW
    const QPixmap &pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), x, y, 2, 2);
#else
    const QPixmap &pixmap = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId(),  x, y, 2, 2);
#endif
    if(!pixmap.isNull())
    {
        const QImage &image = pixmap.toImage();
        if(!image.isNull() && image.valid(0, 0))
        {
            const QColor &color = image.pixel(0, 0);
            const int red = color.red();
            const int green = color.green();
            const int blue= color.blue();

            strDecimal = QString("%1, %2, %3")
                    .arg(red)
                    .arg(green)
                    .arg(blue);
            strHex = QString("#%1%2%3")
                    .arg(QString("%1").arg(red & 0xFF ,2, 16, QLatin1Char('0')).toUpper())
                    .arg(QString("%1").arg(green & 0xFF ,2, 16, QLatin1Char('0')).toUpper())
                    .arg(QString("%1").arg(blue & 0xFF ,2, 16, QLatin1Char('0')).toUpper());
        }
    }

    m_ui->labColor->setStyleSheet(QString("background-color: rgb(%1);").arg(strDecimal));
    m_ui->txtRgb->setText(strDecimal);
    m_ui->txtWeb->setText(strHex);

    QTimer::singleShot(100, this, SLOT(ShowColorValue()));
}
