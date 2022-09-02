#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->btnOpen, SIGNAL(clicked()), SLOT(openFileButtonClicked()));
    connect(m_ui->ckFill, SIGNAL(clicked(bool)), SLOT(fillButtonChanged(bool)));
    connect(m_ui->ckFade, SIGNAL(clicked(bool)), SLOT(fadeButtonChanged(bool)));
    connect(m_ui->ckKeyMove, SIGNAL(clicked(bool)), SLOT(keyMoveButtonChanged(bool)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::openFileButtonClicked()
{
    const QString &path = QFileDialog::getExistingDirectory(this, "选择文件夹");
    if(!path.isEmpty())
    {
        m_ui->labPath->setText(path);
        m_ui->imageView->load(path);
    }
}

void MainWindow::fillButtonChanged(bool state)
{
    m_ui->imageView->setFill(state);
}

void MainWindow::fadeButtonChanged(bool state)
{
    m_ui->imageView->setFade(state);
}

void MainWindow::keyMoveButtonChanged(bool state)
{
    m_ui->imageView->setKeyMove(state);
}
