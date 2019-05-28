#include "mainwindow.h"

#include <QPainter>
#include <QFileDialog>
#include "qrencode/qrencode.h"

QImage makeQRcode(const QString &data, const QSize &size)
{
    QImage image(size, QImage::Format_RGB32);
    image.fill(QColor("#000000"));

    QPainter painter(&image);

    if(!painter.isActive())
    {
        return image;
    }

    QRcode *qrCode = QRcode_encodeString(data.toUtf8().data(), 1, QR_ECLEVEL_H, QR_MODE_8, true);
    if(!qrCode)
    {
        QColor error("#ffffff");
        painter.setBrush(error);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, image.width(), image.height());
        painter.end();

        return image;
    }

    QColor colorForBackground("#ffffff");

    painter.setBrush(colorForBackground);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, image.width(), image.height());

    painter.setBrush(QColor("#000000"));

    const double s =(qrCode->width > 0) ?(qrCode->width) : 1;
    const double aspect = image.width() / image.height();
    const double scale = ((aspect > 1.0) ? image.height() : image.width()) / s;

    for(int y = 0; y < s; ++y)
    {
        const int yy = static_cast<int>(y * s);
        for(int x = 0; x < s; ++x)
        {
            const int xx = yy + x;
            const unsigned char b = qrCode->data[xx];

            if(b & 0x01)
            {
                const double rx1 = x * scale, ry1 = y * scale;
                QRectF r(rx1, ry1, scale, scale);
                painter.drawRects(&r, 1);
            }
        }
    }

    QRcode_free(qrCode);
    painter.end();

    return image;
}

void MainWindow::savePng(const QString &text)
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Path", ".", "*.png");

    if(filePath.isEmpty())
    {
        return;
    }

    if(!filePath.toLower().endsWith(".png"))
    {
        filePath += ".png";
    }

    makeQRcode(text, QSize(475, 475)).save(filePath, "png");
}
