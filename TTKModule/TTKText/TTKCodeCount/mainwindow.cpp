#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initForm();

    connect(ui->btnOpenFile, SIGNAL(clicked(bool)), SLOT(buttonOpenFile()));
    connect(ui->btnOpenPath, SIGNAL(clicked(bool)), SLOT(buttonOpenPath()));
    connect(ui->btnClear, SIGNAL(clicked(bool)), SLOT(buttonClear()));

    buttonClear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initForm()
{
    QStringList headText;
    headText << "文件名" << "类型" << "大小" << "总行数" << "代码行数" << "注释行数" << "空白行数" << "路径";

    QList<int> columnWidth;
    columnWidth << 130 << 50 << 70 << 80 << 70 << 70 << 70 << 150;

    const int columnCount = headText.count();
    ui->tableWidget->setColumnCount(columnCount);
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(20);
    ui->tableWidget->verticalHeader()->setHighlightSections(false);

    for(int i = 0; i < columnCount; i++)
    {
        ui->tableWidget->setColumnWidth(i, columnWidth.at(i));
    }

    ui->txtCount->setStyleSheet("color:#17A086;");
    ui->txtSize->setStyleSheet("color:#CA5AA6;");
    ui->txtRow->setStyleSheet("color:#CD1B19;");
    ui->txtCode->setStyleSheet("color:#22A3A9;");
    ui->txtNote->setStyleSheet("color:#D64D54;");
    ui->txtBlank->setStyleSheet("color:#A279C5;");

    QFont font;
    font.setBold(true);
    if(font.pointSize() > 0)
    {
        font.setPointSize(font.pointSize() + 1);
    }
    else
    {
        font.setPixelSize(font.pixelSize() + 2);
    }

    ui->txtCount->setFont(font);
    ui->txtSize->setFont(font);
    ui->txtRow->setFont(font);
    ui->txtCode->setFont(font);
    ui->txtNote->setFont(font);
    ui->txtBlank->setFont(font);

#if (QT_VERSION > QT_VERSION_CHECK(4,7,0))
    ui->txtFilter->setPlaceholderText("中间空格隔开,例如 *.h *.cpp *.c");
#endif
}

bool MainWindow::checkFile(const QString &fileName)
{
    if(fileName.startsWith("moc_") || fileName.startsWith("ui_") || fileName.startsWith("qrc_"))
    {
        return false;
    }

    QFileInfo file(fileName);
    const QString &suffix = "*." + file.suffix();
    const QString &filter = ui->txtFilter->text().trimmed();
    const QStringList &filters = filter.split(" ");
    return filters.contains(suffix);
}

void MainWindow::countCode(const QString &filePath)
{
    QDir dir(filePath);
    foreach(const QFileInfo &fileInfo , dir.entryInfoList())
    {
        if(fileInfo.isFile())
        {
            if(checkFile(fileInfo.fileName()))
            {
                m_files << fileInfo.filePath();
            }
        }
        else
        {
            if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            {
                continue;
            }
            countCode(fileInfo.absoluteFilePath());
        }
    }
}

void MainWindow::countCode(const QStringList &files)
{
    int lineCode, lineBlank, lineNotes, count = files.count();

    buttonClear();
    ui->tableWidget->setRowCount(count);

    quint32 totalLines = 0;
    quint32 totalBytes = 0;
    quint32 totalCodes = 0;
    quint32 totalNotes = 0;
    quint32 totalBlanks = 0;

    for(int i = 0; i < count; i++)
    {
        QFileInfo fileInfo(files.at(i));
        countCode(fileInfo.filePath(), lineCode, lineBlank, lineNotes);
        int lineAll = lineCode + lineBlank + lineNotes;

        QTableWidgetItem *itemName = new QTableWidgetItem;
        itemName->setText(fileInfo.fileName());

        QTableWidgetItem *itemSuffix = new QTableWidgetItem;
        itemSuffix->setText(fileInfo.suffix());

        QTableWidgetItem *itemSize = new QTableWidgetItem;
        itemSize->setText(QString::number(fileInfo.size()));

        QTableWidgetItem *itemLine = new QTableWidgetItem;
        itemLine->setText(QString::number(lineAll));

        QTableWidgetItem *itemCode = new QTableWidgetItem;
        itemCode->setText(QString::number(lineCode));

        QTableWidgetItem *itemNote = new QTableWidgetItem;
        itemNote->setText(QString::number(lineNotes));

        QTableWidgetItem *itemBlank = new QTableWidgetItem;
        itemBlank->setText(QString::number(lineBlank));

        QTableWidgetItem *itemPath = new QTableWidgetItem;
        itemPath->setText(fileInfo.filePath());

        itemSuffix->setTextAlignment(Qt::AlignCenter);
        itemSize->setTextAlignment(Qt::AlignCenter);
        itemLine->setTextAlignment(Qt::AlignCenter);
        itemCode->setTextAlignment(Qt::AlignCenter);
        itemNote->setTextAlignment(Qt::AlignCenter);
        itemBlank->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(i, 0, itemName);
        ui->tableWidget->setItem(i, 1, itemSuffix);
        ui->tableWidget->setItem(i, 2, itemSize);
        ui->tableWidget->setItem(i, 3, itemLine);
        ui->tableWidget->setItem(i, 4, itemCode);
        ui->tableWidget->setItem(i, 5, itemNote);
        ui->tableWidget->setItem(i, 6, itemBlank);
        ui->tableWidget->setItem(i, 7, itemPath);

        totalBytes  += fileInfo.size();
        totalLines  += lineAll;
        totalCodes  += lineCode;
        totalNotes  += lineNotes;
        totalBlanks += lineBlank;

        if(i % 100 == 0)
        {
            qApp->processEvents();
        }
    }

    m_files.clear();
    ui->txtCount->setText(QString::number(count));
    ui->txtSize->setText(QString::number(totalBytes));
    ui->txtRow->setText(QString::number(totalLines));
    ui->txtCode->setText(QString::number(totalCodes));
    ui->txtNote->setText(QString::number(totalNotes));
    ui->txtBlank->setText(QString::number(totalBlanks));

    double percent = 0.0;
    percent = ((double)totalCodes / totalLines) * 100;
    ui->labPercentCode->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));

    percent = ((double)totalNotes / totalLines) * 100;
    ui->labPercentNote->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));

    percent = ((double)totalBlanks / totalLines) * 100;
    ui->labPercentBlank->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));
}

void MainWindow::countCode(const QString &fileName, int &lineCode, int &lineBlank, int &lineNotes)
{
    lineCode = lineBlank = lineNotes = 0;
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream out(&file);
        QString line;
        bool isNote = false;
        while(!out.atEnd())
        {
            line = out.readLine();
            if(line.startsWith(" "))
            {
                line.remove(" ");
            }

            if(line.startsWith("/*"))
            {
                isNote = true;
            }

            if(isNote)
            {
                lineNotes++;
            }
            else
            {
                if(line.startsWith("//"))
                {
                    lineNotes++;
                }
                else if(line.isEmpty())
                {
                    lineBlank++;
                }
                else
                {
                    lineCode++;
                }
            }

            if(line.endsWith("*/"))
            {
                isNote = false;
            }
        }
    }
}

void MainWindow::buttonOpenFile()
{
    const QString &filter = QString("代码文件(%1)").arg(ui->txtFilter->text().trimmed());
    const QStringList &files = QFileDialog::getOpenFileNames(this, "选择文件", "./", filter);

    if(files.size() > 0)
    {
        ui->txtFile->setText(files.join("|"));
        countCode(files);
    }
}

void MainWindow::buttonOpenPath()
{
    const QString &path = QFileDialog::getExistingDirectory(this, "选择目录", "./",  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!path.isEmpty())
    {
        ui->txtPath->setText(path);
        m_files.clear();
        countCode(path);
        countCode(m_files);
    }
}

void MainWindow::buttonClear()
{
    ui->txtCount->setText("0");
    ui->txtSize->setText("0");
    ui->txtRow->setText("0");

    ui->txtCode->setText("0");
    ui->txtNote->setText("0");
    ui->txtBlank->setText("0");

    ui->labPercentCode->setText("0%");
    ui->labPercentNote->setText("0%");
    ui->labPercentBlank->setText("0%");
    ui->tableWidget->setRowCount(0);
}
