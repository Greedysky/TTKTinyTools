#include "mainwindow.h"

#include <QFileDialog>

void MainWindow::makeWebP()
{
    const QStringList &filePaths = QFileDialog::getOpenFileNames(nullptr, "Save Path", TTK_DOT, "Images (*.png *.jpg)");

    if(filePaths.isEmpty())
    {
        return;
    }

    for(const auto &filePath : qAsConst(filePaths))
    {
        QImage(filePath).save(filePath, "WEBP", 100);
    }
}
