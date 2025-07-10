#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    initialize();

    connect(m_ui->btnOpenFile, SIGNAL(clicked(bool)), SLOT(buttonOpenFile()));
    connect(m_ui->btnOpenPath, SIGNAL(clicked(bool)), SLOT(buttonOpenPath()));
    connect(m_ui->btnClear, SIGNAL(clicked(bool)), SLOT(buttonClear()));

    buttonClear();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::initialize()
{
    QStringList headText;
    headText << "文件名" << "类型" << "大小" << "总行数" << "代码行数" << "注释行数" << "空白行数" << "路径";

    TTKIntList columnWidth;
    columnWidth << 130 << 50 << 70 << 80 << 70 << 70 << 70 << 150;

    const int columnCount = headText.count();
    m_ui->tableWidget->setColumnCount(columnCount);
    m_ui->tableWidget->setHorizontalHeaderLabels(headText);
    m_ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->tableWidget->verticalHeader()->setVisible(false);
    m_ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    m_ui->tableWidget->verticalHeader()->setDefaultSectionSize(20);
    m_ui->tableWidget->verticalHeader()->setHighlightSections(false);

    for(int i = 0; i < columnCount; ++i)
    {
        m_ui->tableWidget->setColumnWidth(i, columnWidth.at(i));
    }

    m_ui->txtCount->setStyleSheet("color:#17A086;");
    m_ui->txtSize->setStyleSheet("color:#CA5AA6;");
    m_ui->txtRow->setStyleSheet("color:#CD1B19;");
    m_ui->txtCode->setStyleSheet("color:#22A3A9;");
    m_ui->txtNote->setStyleSheet("color:#D64D54;");
    m_ui->txtBlank->setStyleSheet("color:#A279C5;");

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

    m_ui->txtCount->setFont(font);
    m_ui->txtSize->setFont(font);
    m_ui->txtRow->setFont(font);
    m_ui->txtCode->setFont(font);
    m_ui->txtNote->setFont(font);
    m_ui->txtBlank->setFont(font);

#if TTK_QT_VERSION_CHECK(4,7,0)
    m_ui->txtFilter->setPlaceholderText("中间空格隔开,例如 *.h *.cpp *.c");
#endif
}

bool MainWindow::checkFile(const QString &fileName)
{
    if(fileName.startsWith("moc_") || fileName.startsWith("ui_") || fileName.startsWith("qrc_"))
    {
        return false;
    }

    const QFileInfo fin(fileName);
    const QString &suffix = "*." + TTK_FILE_SUFFIX(fin);
    const QString &filter = m_ui->txtFilter->text().trimmed();
    const QStringList &filters = filter.split(TTK_SPACE);
    return filters.contains(suffix);
}

void MainWindow::countCode(const QString &filePath)
{
    QDir dir(filePath);
    for(const QFileInfo &fin : dir.entryInfoList())
    {
        if(fin.isFile())
        {
            if(checkFile(fin.fileName()))
            {
                m_files << fin.filePath();
            }
        }
        else
        {
            if(fin.fileName() == TTK_DOT || fin.fileName() == TTK_DOTDOT)
            {
                continue;
            }
            countCode(fin.absoluteFilePath());
        }
    }
}

void MainWindow::countCode(const QStringList &files)
{
    int lineCode, lineBlank, lineNotes, count = files.count();

    buttonClear();
    m_ui->tableWidget->setRowCount(count);

    quint32 totalLines = 0;
    quint32 totalBytes = 0;
    quint32 totalCodes = 0;
    quint32 totalNotes = 0;
    quint32 totalBlanks = 0;

    for(int i = 0; i < count; ++i)
    {
        const QFileInfo fin(files.at(i));
        countCode(fin.filePath(), lineCode, lineBlank, lineNotes);
        int lineAll = lineCode + lineBlank + lineNotes;

        QTableWidgetItem *itemName = new QTableWidgetItem;
        itemName->setText(fin.fileName());

        QTableWidgetItem *itemSuffix = new QTableWidgetItem;
        itemSuffix->setText(TTK_FILE_SUFFIX(fin));

        QTableWidgetItem *itemSize = new QTableWidgetItem;
        itemSize->setText(QString::number(fin.size()));

        QTableWidgetItem *itemLine = new QTableWidgetItem;
        itemLine->setText(QString::number(lineAll));

        QTableWidgetItem *itemCode = new QTableWidgetItem;
        itemCode->setText(QString::number(lineCode));

        QTableWidgetItem *itemNote = new QTableWidgetItem;
        itemNote->setText(QString::number(lineNotes));

        QTableWidgetItem *itemBlank = new QTableWidgetItem;
        itemBlank->setText(QString::number(lineBlank));

        QTableWidgetItem *itemPath = new QTableWidgetItem;
        itemPath->setText(fin.filePath());

        QtItemSetTextAlignment(itemSuffix, Qt::AlignCenter);
        QtItemSetTextAlignment(itemSize, Qt::AlignCenter);
        QtItemSetTextAlignment(itemLine, Qt::AlignCenter);
        QtItemSetTextAlignment(itemCode, Qt::AlignCenter);
        QtItemSetTextAlignment(itemNote, Qt::AlignCenter);
        QtItemSetTextAlignment(itemBlank, Qt::AlignCenter);

        m_ui->tableWidget->setItem(i, 0, itemName);
        m_ui->tableWidget->setItem(i, 1, itemSuffix);
        m_ui->tableWidget->setItem(i, 2, itemSize);
        m_ui->tableWidget->setItem(i, 3, itemLine);
        m_ui->tableWidget->setItem(i, 4, itemCode);
        m_ui->tableWidget->setItem(i, 5, itemNote);
        m_ui->tableWidget->setItem(i, 6, itemBlank);
        m_ui->tableWidget->setItem(i, 7, itemPath);

        totalBytes  += fin.size();
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
    m_ui->txtCount->setText(QString::number(count));
    m_ui->txtSize->setText(QString::number(totalBytes));
    m_ui->txtRow->setText(QString::number(totalLines));
    m_ui->txtCode->setText(QString::number(totalCodes));
    m_ui->txtNote->setText(QString::number(totalNotes));
    m_ui->txtBlank->setText(QString::number(totalBlanks));

    double percent = 0.0;
    percent = (totalCodes * 1.0 / totalLines) * 100;
    m_ui->labPercentCode->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));

    percent = (totalNotes * 1.0 / totalLines) * 100;
    m_ui->labPercentNote->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));

    percent = (totalBlanks * 1.0 / totalLines) * 100;
    m_ui->labPercentBlank->setText(QString("%1%").arg(percent, 5, 'f', 2, QChar(' ')));
}

void MainWindow::countCode(const QString &fileName, int &lineCode, int &lineBlank, int &lineNotes)
{
    lineCode = lineBlank = lineNotes = 0;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream out(&file);
        QString line;
        bool isNote = false;
        while(!out.atEnd())
        {
            line = out.readLine();
            if(line.startsWith(TTK_SPACE))
            {
                line.remove(TTK_SPACE);
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
    const QString &filter = QString("代码文件(%1)").arg(m_ui->txtFilter->text().trimmed());
    const QStringList &files = QFileDialog::getOpenFileNames(this, "选择文件", "./", filter);

    if(files.count() > 0)
    {
        m_ui->txtFile->setText(files.join("|"));
        countCode(files);
    }
}

void MainWindow::buttonOpenPath()
{
    const QString &path = QFileDialog::getExistingDirectory(this, "选择目录", "./",  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!path.isEmpty())
    {
        m_ui->txtPath->setText(path);
        m_files.clear();
        countCode(path);
        countCode(m_files);
    }
}

void MainWindow::buttonClear()
{
    m_ui->txtCount->setText("0");
    m_ui->txtSize->setText("0");
    m_ui->txtRow->setText("0");

    m_ui->txtCode->setText("0");
    m_ui->txtNote->setText("0");
    m_ui->txtBlank->setText("0");

    m_ui->labPercentCode->setText("0%");
    m_ui->labPercentNote->setText("0%");
    m_ui->labPercentBlank->setText("0%");
    m_ui->tableWidget->setRowCount(0);
}
