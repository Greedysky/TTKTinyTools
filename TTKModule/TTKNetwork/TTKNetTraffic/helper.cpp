#include "helper.h"
#include "ttknettrafficlabel.h"
#include "ttkcpumemorylabel.h"

#define KB (1024)
#define MB (1024 * 1024)
#define GB (1024 * 1024 * 1024)

QString size2Number(ulong size)
{
    if(size < KB)
    {
        return QString::number(size*1.0, 'f', 2) + "KB";
    }
    else if(KB <= size && size < MB)
    {
        return QString::number(size*1.0/KB, 'f', 2) + "MB";
    }
    else if(MB <= size && size < GB)
    {
        return QString::number(size*1.0/MB, 'f', 2) + "GB";
    }
    else
    {
        return QString("0KB");
    }
}

Helper::Helper(QObject *parent)
    : QObject(parent)
{
    m_traffic = new TTKNetTraffic(this);
    connect(m_traffic, SIGNAL(networkData(ulong,ulong)), SLOT(setData(ulong,ulong)));

    m_memery = new TTKCPUMemoryLabel(this);

}

Helper::~Helper()
{
    delete m_traffic;
    delete m_memery;
}

void Helper::start()
{
    m_traffic->setAvailableNewtworkName("wlp2s0");
    m_memery->start(500);
}

QString Helper::getNWS() const
{
    return m_nwsInfo;
}

QString Helper::getMem() const
{
    return QString::number(m_memery->memeryInfo());
}

QString Helper::getCPU() const
{
    return QString::number(m_memery->cpuInfo());
}

void Helper::setData(ulong upload, ulong download)
{
    m_nwsInfo = QString(" ↑ %1, ↓ %2").arg(size2Number(upload)).arg(size2Number(download));
}
