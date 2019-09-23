#include "imageview.h"

#include <QTimer>
#include <QAction>
#include <QPainter>
#include <QToolButton>
#include <QKeyEvent>
#include <QFileDialog>

ImageIndex::ImageIndex(QWidget *parent)
    : QWidget(parent)
{
    m_totalNum = 0;
    m_currentIndex = -1;
    setFixedSize(160, 30);
}

void ImageIndex::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBg(&painter);
    drawText(&painter);
}

void ImageIndex::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(46, 132, 243));
    painter->drawRoundedRect(rect(), 2, 2);
    painter->restore();
}

void ImageIndex::drawText(QPainter *painter)
{
    const QString &text = QString("第 %1 张 / 共 %2 张").arg(m_currentIndex + 1).arg(m_totalNum);
    painter->save();
    painter->setPen(Qt::white);

    QFont font;
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(rect(), Qt::AlignCenter, text);
    painter->restore();
}

void ImageIndex::setTotalNum(int totalNum)
{
    if(totalNum < 0)
    {
        m_totalNum = 0;
    }
    else
    {
        m_totalNum = totalNum;
    }

    m_currentIndex = 0;
    update();
}

void ImageIndex::setCurrentIndex(int currentIndex)
{
    if(currentIndex < 0)
    {
        m_currentIndex = -1;
    }
    else
    {
        m_currentIndex = currentIndex;
    }

    update();
}



ImageView::ImageView(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(".QToolButton{background-color:rgba(0,0,0,0);border-style:none;}");

    m_bottomSpace = 10;
    m_buttonSpace = 10;
    m_icoSize = QSize(65, 65);

    m_fade = false;
    m_fill = false;
    m_keyMove = false;

    m_totalNum = 0;
    m_currentIndex = -1;

    m_imageIndex = new ImageIndex(this);
    connect(this, SIGNAL(totalNumChanged(int)), m_imageIndex, SLOT(setTotalNum(int)));
    connect(this, SIGNAL(currentIndexChanged(int)), m_imageIndex, SLOT(setCurrentIndex(int)));

    m_preButton = new QToolButton(this);
    m_nextButton = new QToolButton(this);

    m_preButton->setCursor(Qt::PointingHandCursor);
    m_nextButton->setCursor(Qt::PointingHandCursor);

    m_preButton->setIconSize(m_icoSize);
    m_nextButton->setIconSize(m_icoSize);

    m_preButton->setIcon(QIcon(":/image/btn_pre_normal.png"));
    m_nextButton->setIcon(QIcon(":/image/btn_next_normal.png"));

    connect(m_preButton, SIGNAL(clicked()), this, SLOT(movePrevious()));
    connect(m_nextButton, SIGNAL(clicked()), this, SLOT(moveNext()));

    m_opacity = 1.0;
    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(fading()));

    QAction *action_load = new QAction("载入", this);
    connect(action_load, SIGNAL(triggered(bool)), this, SLOT(load()));
    addAction(action_load);

    QAction *action_clear = new QAction("清空", this);
    connect(action_clear, SIGNAL(triggered(bool)), this, SLOT(clear()));
    addAction(action_clear);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    calcGeometry();
}

ImageView::~ImageView()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
}

void ImageView::calcGeometry()
{
    const QPoint prePoint(m_buttonSpace, (height() - m_preButton->height()) / 2);
    m_preButton->move(prePoint);

    const QPoint nextPoint(width() - m_buttonSpace - m_preButton->width(), (height() - m_preButton->height()) / 2);
    m_nextButton->move(nextPoint);

    const QPoint numPoint(width() / 2 - m_imageIndex->width() / 2, height() - m_bottomSpace - m_preButton->height() / 2 - m_imageIndex->height() / 2);
    m_imageIndex->move(numPoint);
}

void ImageView::fading()
{
    m_opacity += 0.05;
    if(m_opacity > 1.0)
    {
        m_opacity = 1.0;
        m_timer->stop();
    }

    update();
}

void ImageView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBg(&painter);

    if(m_totalNum > 0)
    {
        drawImage(&painter);
    }
}

void ImageView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Up)
    {
        movePrevious();
    }
    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_Down)
    {
        moveNext();
    }
}

void ImageView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    calcGeometry();
}

void ImageView::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    calcGeometry();
}

void ImageView::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawRect(rect());
    painter->restore();
}

void ImageView::drawImage(QPainter *painter)
{
    painter->save();
    painter->setOpacity(m_opacity);

    if(m_fill)
    {
        painter->drawImage(rect(), m_currentImage);
        painter->restore();
    }
    else
    {
        const int imageWidth = m_currentImage.width();
        const int imageHeight = m_currentImage.height();
        const int imageX = rect().center().x() - imageWidth / 2;
        const int imageY = rect().center().y() - imageHeight / 2;
        QPoint point(imageX, imageY);

        painter->drawImage(point, m_currentImage);
        painter->restore();
    }
}

void ImageView::load()
{
    const QString &path = QFileDialog::getExistingDirectory(this, "选择图片文件");
    if(!path.isEmpty())
    {
        load(path);
    }
}

void ImageView::load(const QString &path)
{
    QDir folder(path);
    folder.setSorting(QDir::Time);

    if(folder.exists())
    {
        QStringList filter;
        filter << "*.png" << "*.jpg" << "*.gif" << "*.jpeg" << "*.bmp" ;
        const QStringList &imageList = folder.entryList(filter);

        m_totalNum = imageList.count();
        m_currentIndex = -1;
        m_imageNames.clear();

        if(m_totalNum > 0)
        {
            foreach (QString strImage, imageList)
            {
                const QString &strFullPath = QString("%1/%2").arg(path).arg(strImage);
                m_imageNames.append(strFullPath);
            }

            moveToPage(0);
            emit totalNumChanged(m_totalNum);
        }
    }
}

void ImageView::clear()
{
    m_totalNum = 0;
    m_currentIndex = -1;
    m_imageNames.clear();
    update();

    emit totalNumChanged(m_totalNum);
    emit currentIndexChanged(m_currentIndex);
}

void ImageView::setBottomSpace(int bottomSpace)
{
    if(m_bottomSpace != bottomSpace)
    {
        m_bottomSpace = bottomSpace;
        update();
    }
}

void ImageView::setButtonSpace(int buttonSpace)
{
    if(m_buttonSpace != buttonSpace)
    {
        m_buttonSpace = buttonSpace;
        update();
    }
}

void ImageView::setIcoSize(const QSize &icoSize)
{
    if(m_icoSize != icoSize)
    {
        m_icoSize = icoSize;
        m_preButton->setIconSize(icoSize);
        m_nextButton->setIconSize(icoSize);

        calcGeometry();
        update();
    }
}

void ImageView::setFill(bool fill)
{
    if(m_fill != fill)
    {
        m_fill = fill;
        update();
    }
}

void ImageView::setFade(bool fade)
{
    if(m_fade != fade)
    {
        m_fade = fade;
        update();
    }
}

void ImageView::setKeyMove(bool keyMove)
{
    if(m_keyMove != keyMove)
    {
        m_keyMove = keyMove;
        setFocusPolicy(m_keyMove ? Qt::StrongFocus : Qt::NoFocus);
    }
}

void ImageView::moveFirst()
{
    const int index = 0;
    if(m_currentIndex != index)
    {
        moveToPage(index);
    }
}

void ImageView::moveLast()
{
    const int index = m_totalNum - 1;
    if(m_currentIndex != index)
    {
        moveToPage(index);
    }
}

void ImageView::movePrevious()
{
    if(m_currentIndex > 0)
    {
        m_currentIndex--;
        moveToPage(m_currentIndex);
    }
}

void ImageView::moveNext()
{
    if(m_currentIndex < m_totalNum - 1)
    {
        m_currentIndex++;
        moveToPage(m_currentIndex);
    }
}

void ImageView::moveToPage(int index)
{
    if(m_totalNum == 0 || index > m_totalNum - 1)
    {
        return ;
    }

    m_currentIndex = index;
    m_currentImage = QImage(m_imageNames.at(m_currentIndex));
    emit currentIndexChanged(m_currentIndex);

    if(m_fade)
    {
        m_opacity = 0.0;
        m_timer->start();
    }
    else
    {
        update();
    }
}
