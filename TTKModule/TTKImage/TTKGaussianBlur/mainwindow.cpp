#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gaussianblur.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_ui->valueSlider->setRange(1, 100);

    connect(m_ui->openButton, SIGNAL(clicked(bool)), SLOT(openImage()));
    connect(m_ui->valueSlider, SIGNAL(valueChanged(int)), SLOT(radiusChanged(int)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::openImage()
{
    m_path = QFileDialog::getOpenFileName(this, "Please Image", "", "Image Files (*.png *.bmp *.jpg)");
    if(m_path.isEmpty())
    {
        return;
    }

    m_ui->valueSlider->setValue(1);
    m_ui->originPixLabel->setPixmap(QPixmap(m_path));
    m_ui->resultPixLabel->setPixmap(QPixmap(m_path));
}

void MainWindow::radiusChanged(int value)
{
    if(m_path.isEmpty())
    {
        return;
    }

    QImage image(m_path);
    GaussianBlur().gaussBlur(image, value);
    m_ui->resultPixLabel->setPixmap(QPixmap::fromImage(image));
}
