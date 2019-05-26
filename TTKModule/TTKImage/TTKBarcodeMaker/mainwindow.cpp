#include "mainwindow.h"

#include <QFileDialog>

void paintLine(QImage &image, const bool black, const int pos, const int len = 100)
{
    for(auto index = 0; index < len; ++index)
    {
        image.setPixel(pos * 2, index, (black) ? (qRgba(0, 0, 0, 255)) : (qRgba(0, 0, 0, 0)));
        image.setPixel(pos * 2 + 1, index, (black) ? (qRgba(0, 0, 0, 255)) : (qRgba(0, 0, 0, 0)));
    }
}

void paintLines(QImage &image, const QString &key, const int pos, const int len = 100)
{
    for(auto index = 0; index < 7; ++index)
    {
        paintLine(image, key[ index ] == '1', pos + index, len);
    }
}

void paintByteA(QImage &image, const int number, const int pos)
{
    switch(number)
    {
        case 0: paintLines(image, "0001101", pos); break;
        case 1: paintLines(image, "0011001", pos); break;
        case 2: paintLines(image, "0010011", pos); break;
        case 3: paintLines(image, "0111101", pos); break;
        case 4: paintLines(image, "0100011", pos); break;
        case 5: paintLines(image, "0110001", pos); break;
        case 6: paintLines(image, "0101111", pos); break;
        case 7: paintLines(image, "0111011", pos); break;
        case 8: paintLines(image, "0110111", pos); break;
        case 9: paintLines(image, "0001011", pos); break;
    }
}

void paintByteB(QImage &image, const int number, const int pos)
{
    switch(number)
    {
        case 0: paintLines(image, "0100111", pos); break;
        case 1: paintLines(image, "0110011", pos); break;
        case 2: paintLines(image, "0011011", pos); break;
        case 3: paintLines(image, "0100001", pos); break;
        case 4: paintLines(image, "0011101", pos); break;
        case 5: paintLines(image, "0111001", pos); break;
        case 6: paintLines(image, "0000101", pos); break;
        case 7: paintLines(image, "0010001", pos); break;
        case 8: paintLines(image, "0001001", pos); break;
        case 9: paintLines(image, "0010111", pos); break;
    }
}

void paintByteC(QImage &image, const int number, const int pos)
{
    switch(number)
    {
        case 0: paintLines(image, "1110010", pos); break;
        case 1: paintLines(image, "1100110", pos); break;
        case 2: paintLines(image, "1101100", pos); break;
        case 3: paintLines(image, "1000010", pos); break;
        case 4: paintLines(image, "1011100", pos); break;
        case 5: paintLines(image, "1001110", pos); break;
        case 6: paintLines(image, "1010000", pos); break;
        case 7: paintLines(image, "1000100", pos); break;
        case 8: paintLines(image, "1001000", pos); break;
        case 9: paintLines(image, "1110100", pos); break;
    }
}

QPixmap makeBarcode(const qint64 number)
{
    QImage image(QSize(190, 120), QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));

    auto pos = 0;

    paintLine(image, true,  pos, 120); pos += 1;
    paintLine(image, false, pos, 120); pos += 1;
    paintLine(image, true,  pos, 120); pos += 1;

    paintByteA(image, number / 100000000000 % 10, pos); pos += 7;
    paintByteB(image, number / 10000000000 % 10, pos); pos += 7;
    paintByteB(image, number / 1000000000 % 10, pos); pos += 7;
    paintByteB(image, number / 100000000 % 10, pos); pos += 7;
    paintByteA(image, number / 10000000 % 10, pos); pos += 7;
    paintByteA(image, number / 1000000 % 10, pos); pos += 7;

    paintLine(image, false, pos, 120); pos += 1;
    paintLine(image, true,  pos, 120); pos += 1;
    paintLine(image, false, pos, 120); pos += 1;
    paintLine(image, true,  pos, 120); pos += 1;
    paintLine(image, false, pos, 120); pos += 1;

    paintByteC(image, number / 100000 % 10, pos); pos += 7;
    paintByteC(image, number / 10000 % 10, pos); pos += 7;
    paintByteC(image, number / 1000 % 10, pos); pos += 7;
    paintByteC(image, number / 100 % 10, pos); pos += 7;
    paintByteC(image, number / 10 % 10, pos); pos += 7;
    paintByteC(image, number % 10, pos); pos += 7;

    paintLine(image, true,  pos, 120); pos += 1;
    paintLine(image, false, pos, 120); pos += 1;
    paintLine(image, true,  pos, 120);

    return QPixmap::fromImage(image);
}

void MainWindow::savePng(const QString &id)
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

    render(id).save(filePath, "png");
}

QPixmap MainWindow::render(const QString &id)
{
    if((id.size() == 13) && id.toLongLong())
    {
        return makeBarcode(id.toLongLong());
    }
    else
    {
        return QPixmap();
    }
}
