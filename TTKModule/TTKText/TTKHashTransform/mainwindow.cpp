#include "mainwindow.h"

#include <QCryptographicHash>

void MainWindow::setSource(const QString &string)
{
    m_source = string;
}

void MainWindow::resetSource()
{
    m_source.clear();
}

void MainWindow::resetTarget()
{
    m_target.clear();
}

void MainWindow::clear()
{
    m_source.clear();
    m_target.clear();
}

void MainWindow::cut()
{
    m_source = m_target;
    m_target.clear();
}

void MainWindow::calculateToBase64()
{
    m_target = m_source.toUtf8().toBase64();
}

void MainWindow::calculateFromBase64()
{
    m_target = QByteArray::fromBase64(m_source.toUtf8());
}

void MainWindow::calculateMD4()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Md4).toHex();
}

void MainWindow::calculateMD5()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Md5).toHex();
}

void MainWindow::calculateSha1()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha1).toHex();
}

#if TTK_QT_VERSION_CHECK(5,0,0)
void MainWindow::calculateSha224()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha224).toHex();
}

void MainWindow::calculateSha256()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha256).toHex();
}

void MainWindow::calculateSha384()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha384).toHex();
}

void MainWindow::calculateSha512()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha512).toHex();
}

void MainWindow::calculateSha3_224()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha3_224).toHex();
}

void MainWindow::calculateSha3_256()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha3_256).toHex();
}

void MainWindow::calculateSha3_384()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha3_384).toHex();
}

void MainWindow::calculateSha3_512()
{
    m_target = QCryptographicHash::hash(m_source.toUtf8(), QCryptographicHash::Sha3_512).toHex();
}
#endif
