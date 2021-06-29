#include "videocontrol.h"
#include "barragecore.h"
#include "barrageedit.h"

#include <QPushButton>
#include <QToolButton>
#include <QBoxLayout>
#include <QWidgetAction>
#include <QButtonGroup>
#include <QSlider>
#include <QLabel>
#include <QFileDialog>

VideoControl::VideoControl(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background:black;");

    m_timeSlider = new QSlider(Qt::Horizontal, this);
    m_menuButton = new QToolButton(this);
    m_playButton = new QPushButton(this);

    m_volumnButton = new QToolButton(this);
    m_volumnSlider = new QSlider(Qt::Vertical, this);
    m_volumnSlider->setRange(0, 100);
    m_volumnSlider->setValue(100);

    m_playButton->setIcon(QIcon(":/video/play"));
    m_volumnButton->setIcon(QIcon(":/video/volumn"));
    m_menuButton->setIcon(QIcon(":/video/menu"));

    m_playButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_volumnButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_menuButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_timeSlider->setCursor(QCursor(Qt::PointingHandCursor));
    m_volumnSlider->setCursor(QCursor(Qt::PointingHandCursor));

    m_popupVolumn.setStyleSheet(BarrageCore::MMenuStyle01);
    m_timeSlider->setStyleSheet(BarrageCore::MSliderStyle02);
    m_volumnSlider->setStyleSheet(BarrageCore::MSliderStyle01);
    m_playButton->setStyleSheet(BarrageCore::MPushButtonStyle02);
    m_volumnButton->setStyleSheet(BarrageCore::MToolButtonStyle02);
    m_menuButton->setStyleSheet(BarrageCore::MToolButtonStyle02);

    QVBoxLayout *controlVLayout = new QVBoxLayout(this);
    controlVLayout->setSpacing(0);
    controlVLayout->setContentsMargins(0, 0, 0, 0);
    QWidget *controlBWidget = new QWidget(this);
    QHBoxLayout *controlBLayout = new QHBoxLayout(controlBWidget);
    controlBLayout->setContentsMargins(9, 0, 9, 0);
    controlBLayout->addWidget(m_menuButton);
    controlBLayout->addWidget(m_playButton);
    controlBLayout->addWidget(m_volumnButton);
    controlBLayout->addStretch(1);
    controlBLayout->addWidget(createBarrageWidget(), 15);
    controlBLayout->addStretch(1);
    controlBWidget->setLayout(controlBLayout);
    controlVLayout->addWidget(m_timeSlider);
    controlVLayout->addWidget(controlBWidget);
    setLayout(controlVLayout);

    QWidgetAction *widgetAction = new QWidgetAction(this);
    widgetAction->setDefaultWidget(m_volumnSlider);
    m_popupVolumn.addAction(widgetAction);
    m_volumnButton->setMenu(&m_popupVolumn);
    m_volumnButton->setPopupMode(QToolButton::InstantPopup);

    connect(m_menuButton, SIGNAL(clicked()), SLOT(openFileDialog()));
    connect(m_timeSlider, SIGNAL(sliderReleased()), SLOT(sliderReleased()));
    connect(m_volumnSlider, SIGNAL(valueChanged(int)), parent, SLOT(volumnChanged(int)));
    connect(m_playButton, SIGNAL(clicked()), parent, SLOT(play()));
}

VideoControl::~VideoControl()
{
    delete m_volumnSlider;
    delete m_timeSlider;
    delete m_menuButton;
    delete m_playButton;
    delete m_volumnButton;
}

void VideoControl::setValue(qint64 position) const
{
    m_timeSlider->setValue(position*1000);
}

void VideoControl::durationChanged(qint64 duration) const
{
    m_timeSlider->setRange(0, duration*1000);
}

void VideoControl::setButtonStyle(bool style) const
{
    m_playButton->setIcon(QIcon( style ? ":/video/play" : ":/video/pause"));
}

void VideoControl::setFixedSize(int w, int h)
{
    QWidget::setFixedSize(w, h);
    m_timeSlider->setFixedWidth(w);
}

void VideoControl::sliderReleased()
{
    emit sliderValueChanged(m_timeSlider->value()/1000);
}

void VideoControl::openFileDialog()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles );
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter("MP4 File(*.mp4)");

    if(dialog.exec())
    {
        emit mediaChanged(dialog.selectedFiles().first());
    }
}

void VideoControl::pushBarrageClicked()
{
    m_pushBarrage->setIcon(QIcon(m_pushBarrageOn ? ":/video/on" : ":/video/off"));
    emit pushBarrageChanged(m_pushBarrageOn);
    m_pushBarrageOn = !m_pushBarrageOn;
}

void VideoControl::barrageSizeButtonClicked(int index)
{
    int size = 10;
    switch(index)
    {
        case 1: size = 15; break;
        case 2: size = 20; break;
        case 3: size = 30; break;
    }
    emit barrageSizeButtonChanged(size);
}

void VideoControl::barrageColorButtonClicked(int index)
{
    QColor color(0, 0, 0);
    switch(index)
    {
        case 1: color = QColor(255, 255, 255); break;
        case 2: color = QColor(255, 0, 0); break;
        case 3: color = QColor(255, 165, 0); break;
        case 4: color = QColor(255, 255, 0); break;
        case 5: color = QColor(0, 255, 0); break;
        case 6: color = QColor(0, 0, 255);  break;
        case 7: color = QColor(160, 32, 240); break;
        case 8: color = QColor(0, 0, 0); break;
    }
    emit barrageColorButtonChanged(color);
}

QWidget* VideoControl::createBarrageWidget()
{
    QWidget *barrageWidget = new QWidget(this);
    m_pushBarrageOn = false;

    ///////////////////////////////////////////
    QWidgetAction *widgetAction = new QWidgetAction(barrageWidget);
    QWidget *barrageSettingWidget = new QWidget(barrageWidget);
    QVBoxLayout *settingLayout = new QVBoxLayout(barrageSettingWidget);

    QWidget *fontSizeWidget = new QWidget(barrageSettingWidget);
    QHBoxLayout *fontSizeLayout = new QHBoxLayout(fontSizeWidget);
    fontSizeLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *fontSizeLabel = new QLabel(tr("Size"), this);

    QButtonGroup *fontSizeButtonGroup = new QButtonGroup(fontSizeWidget);
    fontSizeLayout->addWidget(fontSizeLabel);
    for(int i=1; i<=3; ++i)
    {
        QPushButton *button = createBarrageSizeButton(i);
        fontSizeButtonGroup->addButton(button, i);
        fontSizeLayout->addStretch(1);
        fontSizeLayout->addWidget(button);
    }
    fontSizeLayout->addStretch(1);
    fontSizeWidget->setLayout(fontSizeLayout);
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(fontSizeButtonGroup, SIGNAL(idClicked(int)), SLOT(barrageSizeButtonClicked(int)));
#else
    connect(fontSizeButtonGroup, SIGNAL(buttonClicked(int)), SLOT(barrageSizeButtonClicked(int)));
#endif

    QWidget *backgroundWidget = new QWidget(barrageSettingWidget);
    QHBoxLayout *backgroundLayout = new QHBoxLayout(backgroundWidget);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->setSpacing(5);
    QLabel *backgroundLabel = new QLabel(tr("BgColor"), this);

    QButtonGroup *backgroundButtonGroup = new QButtonGroup(backgroundWidget);
    backgroundLayout->addWidget(backgroundLabel);
    for(int i=1; i<=8; ++i)
    {
        QPushButton *button = createBarrageColorButton(i);
        backgroundButtonGroup->addButton(button, i);
        backgroundLayout->addWidget(button);
    }
    backgroundWidget->setLayout(backgroundLayout);
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(backgroundButtonGroup, SIGNAL(idClicked(int)), SLOT(barrageColorButtonClicked(int)));
#else
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(int)), SLOT(barrageColorButtonClicked(int)));
#endif

    settingLayout->addWidget(fontSizeWidget);
    settingLayout->addWidget(backgroundWidget);
    barrageSettingWidget->setLayout(settingLayout);

    widgetAction->setDefaultWidget(barrageSettingWidget);
    m_popupBarrage.addAction(widgetAction);
    ///////////////////////////////////////////

    QHBoxLayout *barrageLayout = new QHBoxLayout(barrageWidget);
    barrageLayout->setContentsMargins(0, 0, 0, 0);

    QToolButton *menuBarrage = new QToolButton(barrageWidget);
    menuBarrage->setStyleSheet(BarrageCore::MToolButtonStyle02);
    menuBarrage->setIcon(QIcon(":/video/barrageStyle"));
    menuBarrage->setMenu(&m_popupBarrage);
    menuBarrage->setPopupMode(QToolButton::InstantPopup);
    BarrageEdit *lineEditBarrage = new BarrageEdit(barrageWidget);
    lineEditBarrage->addFilterText(tr("just one barrage!"));
    lineEditBarrage->setStyleSheet(BarrageCore::MLineEditStyle01 + \
                                   "QLineEdit{color:white;}");
    connect(lineEditBarrage, SIGNAL(enterFinished(QString)), SIGNAL(addBarrageChanged(QString)));

    QLabel *labelBarrage = new QLabel(barrageWidget);
    labelBarrage->setStyleSheet("color:white;");
    labelBarrage->setText(tr("openBarrage"));
    m_pushBarrage = new QPushButton(barrageWidget);
    m_pushBarrage->setIconSize(QSize(40, 25));
    pushBarrageClicked();
    connect(m_pushBarrage, SIGNAL(clicked()), SLOT(pushBarrageClicked()));

    barrageLayout->addWidget(menuBarrage);
    barrageLayout->addWidget(lineEditBarrage);
    barrageLayout->addWidget(labelBarrage);
    barrageLayout->addWidget(m_pushBarrage);
    barrageWidget->setLayout(barrageLayout);

    return barrageWidget;
}

QPushButton* VideoControl::createBarrageSizeButton(int index)
{
    QPushButton *button = new QPushButton(this);
    switch(index)
    {
        case 1: button->setText(tr("S")); break;
        case 2: button->setText(tr("M")); break;
        case 3: button->setText(tr("G")); break;
    }
    button->setFixedSize(25, 15);
    button->setStyleSheet(BarrageCore::MPushButtonStyle02);
    button->setCursor(QCursor(Qt::PointingHandCursor));
    return button;
}

QPushButton* VideoControl::createBarrageColorButton(int index)
{
    QPushButton *button = new QPushButton(this);
    switch(index)
    {
        case 1: button->setIcon(QIcon(":/color/white")); break;
        case 2: button->setIcon(QIcon(":/color/red")); break;
        case 3: button->setIcon(QIcon(":/color/orange")); break;
        case 4: button->setIcon(QIcon(":/color/yellow")); break;
        case 5: button->setIcon(QIcon(":/color/green")); break;
        case 6: button->setIcon(QIcon(":/color/blue")); break;
        case 7: button->setIcon(QIcon(":/color/purple")); break;
        case 8: button->setIcon(QIcon(":/color/black")); break;
    }
    button->setFixedSize(15, 15);
    button->setStyleSheet(BarrageCore::MPushButtonStyle02);
    button->setCursor(QCursor(Qt::PointingHandCursor));
    return button;
}
