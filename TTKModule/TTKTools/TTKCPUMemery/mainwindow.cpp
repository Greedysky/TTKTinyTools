#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "showcpumemory.h"
#include "showdevicesize.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    ShowCPUMemory *showCPUMemory = new ShowCPUMemory(this);
    showCPUMemory->setLab(ui->labCPUMemory);
    showCPUMemory->start(1000);

    ShowDeviceSize::instance()->setTableWidget(ui->tableWidget);
    ShowDeviceSize::instance()->load();
}
