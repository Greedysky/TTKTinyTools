#include "chinesehelper.h"

#ifdef Q_CC_GNU
#  pragma GCC diagnostic ignored "-Wmultichar"
#endif

ChineseHelper::ChineseHelper()
{
    m_data = PinyinResource::getChineseResource();
}

QChar ChineseHelper::convertToSimplifiedChinese(const QChar &c) const
{
    const QString &simplifiedChinese = m_data.value(c);
    return simplifiedChinese.isEmpty() ? c : simplifiedChinese.at(0);
}

QChar ChineseHelper::convertToTraditionalChinese(const QChar &c) const
{
    const QString &simpTraditionaChinese = m_data.key(c);
    return simpTraditionaChinese.isEmpty() ? c : simpTraditionaChinese.at(0);
}

QString ChineseHelper::convertToSimplifiedChinese(const QString &str) const
{
    QString sb;
    for(int i=0, len=str.length(); i<len; i++)
    {
        sb += convertToSimplifiedChinese(str[i]);
    }
    return sb;
}

QString ChineseHelper::convertToTraditionalChinese(const QString &str) const
{
    QString sb;
    for(int i=0, len=str.length(); i<len; i++)
    {
        sb += convertToTraditionalChinese(str[i]);
    }
    return sb;
}

bool ChineseHelper::isTraditionalChinese(const QChar &c) const
{
    return m_data.keys().indexOf(c) != -1;
}

bool ChineseHelper::isChinese(const QChar &c) const
{
#ifdef Q_CC_MSVC
    return '\xa9\x96' == c || (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5);
#else
    return L'〇' == c || (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5);
#endif
}

bool ChineseHelper::containsChinese(const QString &str) const
{
    for(int i=0, len=str.length(); i<len; i++)
    {
        if(isChinese(str[i]))
        {
            return true;
        }
    }
    return false;
}
