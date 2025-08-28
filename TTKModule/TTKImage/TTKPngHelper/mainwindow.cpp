#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->pushButton, SIGNAL(clicked(bool)), SLOT(chooseImage()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

static QFileInfoList fileListByPath(const QString &dpath, const QStringList &filter, bool recursively)
{
    const QDir dir(dpath);
    if(!dir.exists())
    {
        return QFileInfoList();
    }

    QFileInfoList fileList = dir.entryInfoList(filter, QDir::Files | QDir::Hidden);
    if(recursively)
    {
        const QFileInfoList &folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(const QFileInfo &fin : qAsConst(folderList))
        {
            fileList.append(fileListByPath(fin.absoluteFilePath(), filter, recursively));
        }
    }

    return fileList;
}

void MainWindow::chooseImage()
{
    const QString &dir = QFileDialog::getExistingDirectory(this, "Please Choose PNG Dir First");
    if(dir.isEmpty())
    {
        return;
    }

    QStringList filters;
    filters << "*.png";
    for(const QFileInfo &fin : fileListByPath(dir, filters, true))
    {
        QImage image(fin.absoluteFilePath());
        if(image.isNull())
        {
            continue;
        }

        if(!image.save(fin.absoluteFilePath(), "png"))
        {
            QMessageBox::warning(this, "Error", QString("%1 save fail").arg(fin.absoluteFilePath()));
        }
    }

    QMessageBox::information(this, "Done", "All png image processing is completed");
}
