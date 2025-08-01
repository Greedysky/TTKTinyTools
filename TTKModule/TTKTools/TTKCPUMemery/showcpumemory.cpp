#include "showcpumemory.h"

#include <QTimer>
#include <QProcess>
#include <QLabel>

#ifdef Q_OS_WIN
#  define WIN32_LEAN_AND_MEAN
#  include <qt_windows.h>
#endif

ShowCPUMemory::ShowCPUMemory(QObject *parent)
    : QObject(parent),
      m_totalNew(0),
      m_idleNew(0),
      m_totalOld(0),
      m_idleOld(0),
      m_cpuPercent(0),
      m_memoryPercent(0),
      m_memoryAll(0),
      m_memoryUse(0),
      m_memoryFree(0),
      m_labCPUMemory(nullptr)
{
    m_timerCPU = new QTimer(this);
    connect(m_timerCPU, SIGNAL(timeout()), SLOT(cpu()));

    m_timerMemory = new QTimer(this);
    connect(m_timerMemory, SIGNAL(timeout()), SLOT(memory()));

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(readyRead()), SLOT(readData()));
}

void ShowCPUMemory::setLab(QLabel *label)
{
    m_labCPUMemory = label;
    cpu();
    memory();
}

void ShowCPUMemory::start(int interval)
{
    m_timerCPU->start(interval);
    m_timerMemory->start(interval + 200);
}

void ShowCPUMemory::stop()
{
    m_timerCPU->stop();
    m_timerMemory->stop();
}

void ShowCPUMemory::cpu()
{
#ifdef Q_OS_WIN
    static FILETIME preidleTime;
    static FILETIME prekernelTime;
    static FILETIME preuserTime;

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    quint64 a, b;
    int idle, kernel, user;

    a = (preidleTime.dwHighDateTime << 31) | preidleTime.dwLowDateTime;
    b = (idleTime.dwHighDateTime << 31) | idleTime.dwLowDateTime;
    idle = b -a;

    a = (prekernelTime.dwHighDateTime << 31) | prekernelTime.dwLowDateTime;
    b = (kernelTime.dwHighDateTime << 31) | kernelTime.dwLowDateTime;
    kernel = b -a;

    a = (preuserTime.dwHighDateTime << 31) | preuserTime.dwLowDateTime;
    b = (userTime.dwHighDateTime << 31) | userTime.dwLowDateTime;
    user = b -a;

    m_cpuPercent = (kernel + user - idle) * 100 / (kernel + user);

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime;

    const QString &msg = QString("CPU : %1%  Memery : %2% ( Use %3 MB / All %4 MB )")
                                .arg(m_cpuPercent).arg(m_memoryPercent).arg(m_memoryUse).arg(m_memoryAll);
    m_labCPUMemory->setText(msg);
#else
    if(m_process->state() == QProcess::NotRunning)
    {
        m_totalNew = m_idleNew = 0;
        m_process->start("cat", {"/proc/stat"});
    }
#endif
}

void ShowCPUMemory::memory()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    m_memoryPercent = statex.dwMemoryLoad;
    m_memoryAll = statex.ullTotalPhys / TTK_SN_MB2B;
    m_memoryFree = statex.ullAvailPhys / TTK_SN_MB2B;
    m_memoryUse = m_memoryAll - m_memoryFree;

    const QString &msg = QString("CPU : %1%  Memery : %2% ( Use %3 MB / All %4 MB )")
                                .arg(m_cpuPercent).arg(m_memoryPercent).arg(m_memoryUse).arg(m_memoryAll);
    m_labCPUMemory->setText(msg);
#else
    if(m_process->state() == QProcess::NotRunning)
    {
        m_process->start("cat", {"/proc/meminfo"});
    }
#endif
}

void ShowCPUMemory::readData()
{
    while(!m_process->atEnd())
    {
        QString s = QLatin1String(m_process->readLine());
        if(s.startsWith("cpu"))
        {
            const QStringList &list = s.split(TTK_SPACE);
            m_idleNew = list.at(5).toInt();
            for(const QString &value : qAsConst(list))
            {
                m_totalNew += value.toInt();
            }

            const int total = m_totalNew - m_totalOld;
            const int idle = m_idleNew - m_idleOld;
            m_cpuPercent = 100 * (total - idle) / total;
            m_totalOld = m_totalNew;
            m_idleOld = m_idleNew;
            break;
        }
        else if(s.startsWith("MemTotal"))
        {
            s = s.replace(TTK_SPACE, "");
            s = s.split(":").at(1);
            m_memoryAll = s.left(s.length() - 3).toInt() / TTK_SN_KB2B;
        }
        else if(s.startsWith("MemFree"))
        {
            s = s.replace(TTK_SPACE, "");
            s = s.split(":").at(1);
            m_memoryFree = s.left(s.length() - 3).toInt() / TTK_SN_KB2B;
        }
        else if(s.startsWith("Buffers"))
        {
            s = s.replace(TTK_SPACE, "");
            s = s.split(":").at(1);
            m_memoryFree += s.left(s.length() - 3).toInt() / TTK_SN_KB2B;
        }
        else if(s.startsWith("Cached"))
        {
            s = s.replace(TTK_SPACE, "");
            s = s.split(":").at(1);
            m_memoryFree += s.left(s.length() - 3).toInt() / TTK_SN_KB2B;
            m_memoryUse = m_memoryAll - m_memoryFree;
            m_memoryPercent = 100 * m_memoryUse / m_memoryAll;
            break;
        }
    }

    const QString &msg = QString("CPU : %1%  Memery : %2% ( Use %3 MB / All %4 MB )")
                                .arg(m_cpuPercent).arg(m_memoryPercent).arg(m_memoryUse).arg(m_memoryAll);
    m_labCPUMemory->setText(msg);
}
