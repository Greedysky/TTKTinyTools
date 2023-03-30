#include "helper.h"
#include "ttknettrafficlabel.h"
#include "ttkcpumemorylabel.h"
#include "ttknumberdefine.h"

QString size2Number(qint64 size)
{
    if(size < MH_KB2B)
    {
        return QString::number(size * 1.0, 'f', 1) + "B/s";
    }
    else if(MH_KB2B <= size && size < MH_MB2B)
    {
        return QString::number(size * 1.0 / MH_KB2B, 'f', 1) + "KB/s";
    }
    else if(MH_MB2B <= size && size < MH_GB2B)
    {
        return QString::number(size * 1.0 / MH_MB2B, 'f', 1) + "MB/s";
    }
    else if(MH_GB2B <= size && size < MH_TB2B)
    {
        return QString::number(size * 1.0 / MH_GB2B, 'f', 1) + "GB/s";
    }
    else
    {
        return QString::number(size * 1.0 / MH_TB2B, 'f', 1) + "TB/s";
    }
}

Helper::Helper(QObject *parent)
    : QObject(parent)
{
    m_traffic = new TTKNetTraffic(this);
    m_memery = new TTKCPUMemoryLabel(this);

    connect(m_traffic, SIGNAL(networkData(ulong,ulong)), SLOT(setData(ulong,ulong)));
}

Helper::~Helper()
{
    delete m_traffic;
    delete m_memery;
}

void Helper::start()
{
    m_traffic->setAvailableNewtworkName("wlp2s0");
    m_traffic->stop();
    m_traffic->start();
    m_memery->start(500);
}

QString Helper::speed() const
{
    return m_nwsInfo;
}

QString Helper::memery() const
{
    return QString::number(m_memery->memeryInfo());
}

QString Helper::cpu() const
{
    return QString::number(m_memery->cpuInfo());
}

void Helper::setData(ulong upload, ulong download)
{
    m_nwsInfo = QString(" ↑ %1, ↓ %2").arg(size2Number(upload), size2Number(download));
}
