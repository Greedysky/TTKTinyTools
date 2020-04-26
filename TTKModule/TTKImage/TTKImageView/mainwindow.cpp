#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnOpen, SIGNAL(clicked()), SLOT(openFileButtonClicked()));
    connect(ui->ckFill, SIGNAL(clicked(bool)), SLOT(fillButtonChanged(bool)));
    connect(ui->ckFade, SIGNAL(clicked(bool)), SLOT(fadeButtonChanged(bool)));
    connect(ui->ckKeyMove, SIGNAL(clicked(bool)), SLOT(keyMoveButtonChanged(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileButtonClicked()
{
    const QString &path = QFileDialog::getExistingDirectory(this, "选择文件夹");
    if(!path.isEmpty())
    {
        ui->labPath->setText(path);
        ui->imageView->load(path);
    }
}

void MainWindow::fillButtonChanged(bool state)
{
    ui->imageView->setFill(state);
}

void MainWindow::fadeButtonChanged(bool state)
{
    ui->imageView->setFade(state);
}

void MainWindow::keyMoveButtonChanged(bool state)
{
    ui->imageView->setKeyMove(state);
}
