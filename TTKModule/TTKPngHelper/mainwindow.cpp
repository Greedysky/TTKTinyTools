#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->pushButton, SIGNAL(clicked(bool)), SLOT(choosePng()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::choosePng()
{
    const QStringList paths = QFileDialog::getOpenFileNames(this, "Please choose PNG", QString(), "*.png");
    if(paths.isEmpty())
    {
        return;
    }

    foreach(const QString &path, paths)
    {
        QImage image(path);
        if(image.isNull())
        {
            continue;
        }

        if(!image.save(path, "PNG"))
        {
            QMessageBox::warning(this, "Error", QString("%1 save fail").arg(path));
        }
    }

    QMessageBox::information(this, "Done", "All png image processing is completed");
}
