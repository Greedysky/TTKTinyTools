#include "mainwindow.h"

#include <QFileDialog>

#include "zxing/common/GlobalHistogramBinarizer.h"
#include "zxing/Binarizer.h"
#include "zxing/BinaryBitmap.h"
#include "zxing/MultiFormatReader.h"
#include "zxing/DecodeHints.h"
#include "zxing/LuminanceSource.h"

class ImageWrapper : public zxing::LuminanceSource
{
public:
    ImageWrapper(const QImage &source)
        : LuminanceSource(source.width(), source.height()),
          m_image(source)
    {

    }

    virtual zxing::ArrayRef<char> getRow(int y, zxing::ArrayRef<char> row) const override final
    {
        int width = getWidth();

        if(row->size() != width)
        {
            row.reset(zxing::ArrayRef<char>(width));
        }

        for(int x = 0; x < width; ++x)
        {
            row[x] = TTKStaticCast(char, qGray( m_image.pixel(x, y)));
        }

        return row;
    }

    virtual zxing::ArrayRef<char> getMatrix() const override final
    {
        int width = m_image.width();
        int height = m_image.height();
        char *matrix = new char[width * height];
        char *m = matrix;

        for(int y = 0; y < height; ++y)
        {
            zxing::ArrayRef<char> tmpRow;
            tmpRow = getRow( y, zxing::ArrayRef<char>( width));
#if __cplusplus > 199711L
            memcpy( m, tmpRow->values().data(), width);
#else
            memcpy( m, &tmpRow->values()[0], width);
#endif
            m += width * sizeof(unsigned char);
        }

        zxing::ArrayRef<char> arr = zxing::ArrayRef<char>(matrix, width*height);

        if(matrix)
        {
            delete[] matrix;
        }

        return arr;
    }

private:
    QImage m_image;

};

QString MainWindow::decodeImage(const int decode)
{
    const QString &filePath = QFileDialog::getOpenFileName(nullptr, "Please Path", TTK_DOT, "Image Files (*.png *.jpg)");

    if(filePath.isEmpty())
    {
        return {};
    }

    QImage image;
    if(image.load(filePath))
    {
        return decodeImage(image, decode) ;
    }

    return {};
}

QString MainWindow::decodeImage(const QImage &image, const int decode)
{
    zxing::Ref< zxing::Result > res;

    if(image.isNull())
    {
        return {};
    }

    zxing::MultiFormatReader *reader = new zxing::MultiFormatReader;
    ImageWrapper* ciw = new ImageWrapper( image);

    zxing::Ref< zxing::LuminanceSource > imageRef( ciw);
    zxing::GlobalHistogramBinarizer* binz = new zxing::GlobalHistogramBinarizer( imageRef);

    zxing::Ref< zxing::Binarizer > bz( binz);
    zxing::BinaryBitmap *bb = new zxing::BinaryBitmap( bz);

    zxing::Ref< zxing::BinaryBitmap > ref( bb);

    try
    {
        res = reader->decode(ref, TTKStaticCast(zxing::DecodeHints, TTKStaticCast(unsigned int, decode)));
        return QString( res->getText()->getText().c_str());
    }
    catch(zxing::Exception &)
    {
        return {};
    }
}
