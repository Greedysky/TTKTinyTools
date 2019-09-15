#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpen_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "选择文件夹");

    if (!path.isEmpty()) {
        ui->labPath->setText(path);
        ui->imageView->load(path);
    }
}

void MainWindow::on_ckFill_stateChanged(int arg1)
{
    ui->imageView->setFill(arg1 != 0);
}

void MainWindow::on_ckFade_stateChanged(int arg1)
{
    ui->imageView->setFade(arg1 != 0);
}

void MainWindow::on_ckKeyMove_stateChanged(int arg1)
{
    ui->imageView->setKeyMove(arg1 != 0);
}
