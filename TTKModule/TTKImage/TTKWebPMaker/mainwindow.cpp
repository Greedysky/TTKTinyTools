#include "mainwindow.h"

#include <QFileDialog>

void MainWindow::makeWebP()
{
    const QStringList &filePaths = QFileDialog::getOpenFileNames(nullptr, "Save Path", ".", "Images (*.png *.jpg)");

    if(filePaths.isEmpty())
    {
        return;
    }

    for(const auto &filePath: filePaths)
    {
        QImage(filePath).save(filePath, "WEBP", 100);
    }
}
