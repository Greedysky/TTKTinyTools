#include "mainwindow.h"

#include <QFileDialog>
#include <QApplication>

void MainWindow::save()
{
    const QString &filePath = QFileDialog::getOpenFileName(nullptr, "Please Path", ".", "*.png *.jpg");

    if(filePath.isEmpty())
    {
        return;
    }

    if(!source_.load(filePath))
    {
        return;
    }

    if(source_.isNull())
    {
        return;
    }

    const QString &outPath = QApplication::applicationDirPath();
    //OSX
    if(!QDir().mkpath(outPath + "/OSX/icon.iconset"))
    {
        return;
    }
    save(outPath + "/OSX/icon.iconset/icon_16x16.png", QSize(16, 16));
    save(outPath + "/OSX/icon.iconset/icon_16x16@2x.png", QSize(32, 32));
    save(outPath + "/OSX/icon.iconset/icon_32x32.png", QSize(32, 32));
    save(outPath + "/OSX/icon.iconset/icon_32x32@2x.png", QSize(64, 64));
    save(outPath + "/OSX/icon.iconset/icon_128x128.png", QSize(128, 128));
    save(outPath + "/OSX/icon.iconset/icon_128x128@2x.png", QSize(256, 256));
    save(outPath + "/OSX/icon.iconset/icon_256x256.png", QSize(256, 256));
    save(outPath + "/OSX/icon.iconset/icon_256x256@2x.png", QSize(512, 512));
    save(outPath + "/OSX/icon.iconset/icon_512x512.png", QSize(512, 512));
    save(outPath + "/OSX/icon.iconset/icon_512x512@2x.png", QSize(1024, 1024));

    //OSX
    if(!QDir().mkpath(outPath + "/iOS"))
    {
        return;
    }
    save(outPath + "/iOS/Icon_29x29.png", QSize(29, 29));
    save(outPath + "/iOS/Icon_29x29@2x.png" ,QSize(58, 58));
    save(outPath + "/iOS/Icon_29x29@3x.png", QSize(87, 87));
    save(outPath + "/iOS/Icon_40x40.png", QSize(40, 40));
    save(outPath + "/iOS/Icon_40x40@2x.png", QSize(80, 80));
    save(outPath + "/iOS/Icon_40x40@3x.png", QSize(120, 120));
    save(outPath + "/iOS/Icon_50x50.png", QSize(50, 50));
    save(outPath + "/iOS/Icon_50x50@2x.png", QSize(100, 100));
    save(outPath + "/iOS/Icon_57x57.png", QSize(57, 57));
    save(outPath + "/iOS/Icon_57x57@2x.png", QSize(114, 114));
    save(outPath + "/iOS/Icon_60x60@2x.png", QSize(120, 120));
    save(outPath + "/iOS/Icon_60x60@3x.png", QSize(180, 180));
    save(outPath + "/iOS/Icon_72x72.png", QSize(72, 72));
    save(outPath + "/iOS/Icon_72x72@2x.png", QSize(144, 144));
    save(outPath + "/iOS/Icon_76x76.png", QSize(76, 76));
    save(outPath + "/iOS/Icon_76x76@2x.png", QSize(152, 152));
    save(outPath + "/iOS/Icon_83.5x83.5@2x.png", QSize(167, 167));

    //Android
    if(!QDir().mkpath(outPath + "/Android"))
    {
        return;
    }
    save(outPath + "/Android/Icon_36.png", QSize(36, 36));
    save(outPath + "/Android/Icon_72.png", QSize(72, 72));
    save(outPath + "/Android/Icon_96.png", QSize(96, 96));
}

void MainWindow::save(const QString &path, const QSize &size)
{
    if(!source_.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ).save(path, "png"))
    {
        return;
    }
}
