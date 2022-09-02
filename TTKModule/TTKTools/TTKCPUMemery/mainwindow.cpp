#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "showcpumemory.h"
#include "showdevicesize.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::initialize()
{
    ShowCPUMemory *showCPUMemory = new ShowCPUMemory(this);
    showCPUMemory->setLab(m_ui->labCPUMemory);
    showCPUMemory->start(1000);

    ShowDeviceSize::instance()->setTableWidget(m_ui->tableWidget);
    ShowDeviceSize::instance()->load();
}
