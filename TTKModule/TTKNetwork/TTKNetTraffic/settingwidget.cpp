#include "settingwidget.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QApplication>

SettingWidget::SettingWidget(bool top, bool cpu, bool mem, const QPoint &pos, QWidget *parent)
    : QWidget(parent)
{
    m_topBox = new QCheckBox(this);
    m_topBox->setText("显示在窗体前端");
    if(top)
    {
        m_topBox->setCheckState(Qt::Checked);
    }
    connect(m_topBox, SIGNAL(stateChanged(int)), SIGNAL(showtop(int)));

    m_cpubox = new QCheckBox(this);
    m_cpubox->setText("显示cpu信息");
    if(cpu)
    {
        m_cpubox->setCheckState(Qt::Checked);
    }
    connect(m_cpubox, SIGNAL(stateChanged(int)), SIGNAL(showcpu(int)));

    m_membox = new QCheckBox(this);
    m_membox->setText("显示内存信息");
    if(mem)
    {
        m_membox->setCheckState(Qt::Checked);
    }
    connect(m_membox, SIGNAL(stateChanged(int)), SIGNAL(showmem(int)));

    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, SIGNAL(clicked()), SLOT(close()));

    QPushButton *quitButton = new QPushButton("Quit", this);
    connect(quitButton, SIGNAL(clicked()), SLOT(windowQuit()));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(quitButton);

    QVBoxLayout *allLayout = new QVBoxLayout();
    allLayout->addWidget(m_topBox);
    allLayout->addWidget(m_cpubox);
    allLayout->addWidget(m_membox);
    allLayout->addLayout(buttonLayout);

    setLayout(allLayout);
    setWindowTitle("设置");
    setMinimumWidth(170);
    move(pos.x() + 10, pos.y() - 125);
}

void SettingWidget::windowQuit()
{
    close();
    qApp->closeAllWindows();
}
