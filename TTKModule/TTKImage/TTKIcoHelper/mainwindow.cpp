#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_ui->comboBox->addItem("12x12", 12);
    m_ui->comboBox->addItem("16x16", 16);
    m_ui->comboBox->addItem("24x24", 24);
    m_ui->comboBox->addItem("32x32", 32);
    m_ui->comboBox->addItem("48x48", 48);
    m_ui->comboBox->addItem("64x64", 64);
    m_ui->comboBox->addItem("72x72", 72);
    m_ui->comboBox->addItem("96x96", 96);
    m_ui->comboBox->addItem("128x128", 128);
    m_ui->comboBox->addItem("256x256", 256);
    m_ui->comboBox->addItem("512x512", 512);
    m_ui->comboBox->addItem("1024x1024", 1024);
    m_ui->comboBox->addItem("--", 0);

    connect(m_ui->convertButton, SIGNAL(clicked(bool)), SLOT(convert()));
    connect(m_ui->chooseButton, SIGNAL(clicked(bool)), SLOT(chooseImage()));
    connect(m_ui->comboBox, SIGNAL(currentIndexChanged(int)), SLOT(sizeTypeChanged(int)));

    sizeTypeChanged(3);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::convert()
{
    int w, h;
    if(m_ui->comboBox->currentText() == "--")
    {
        w = m_ui->xlineEdit->text().toInt();
        h = m_ui->ylineEdit->text().toInt();
    }
    else
    {
        const int v = m_ui->comboBox->itemData(m_ui->comboBox->currentIndex()).toInt();
        w = v;
        h = v;
    }

    QFileInfo fin(m_path);
    const QString &path = fin.absolutePath() + "/" + fin.baseName() + QString("_%1x%2.ico").arg(w).arg(h);
    const QPixmap &pix = QPixmap(m_path).scaled(w, h);
    TTK_INFO_STREAM("Save path:" << path << "is" << pix.save(path));
}

void MainWindow::chooseImage()
{
    const QString &path = QFileDialog::getOpenFileName(this, {}, QDir::currentPath(), "Image Files (*.png *.bmp *.jpg)");
    if(path.isEmpty())
    {
        return;
    }

    m_path = path;
    m_ui->label->setScaledContents(true);
    m_ui->label->setPixmap(QPixmap(m_path));
}

void MainWindow::sizeTypeChanged(int index)
{
    m_ui->widget->setVisible(m_ui->comboBox->itemText(index) == "--");
}
