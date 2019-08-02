#include "pinyinhelper.h"

#include <QSet>
#ifdef Q_CC_GNU
#  pragma GCC diagnostic ignored "-Wmultichar"
#endif

PinyinHelper::PinyinHelper()
{
    m_pinyinTable = PinyinResource::getPinyinResource();
    m_mutliPinyinTable = PinyinResource::getMutilPinyinResource();
    m_pinyinSeparator = ",";
#ifdef Q_CC_MSVC
    m_chineseLing = '\xa9\x96';
#else
    m_chineseLing = L'〇';
#endif
    m_allUnmarkedVowel = "aeiouv";
    m_allMarkedVowel = "āáǎàēéěèīíǐìōóǒòūúǔùǖǘǚǜ";
}

QStringList PinyinHelper::convertToPinyinArray(const QChar &c)
{
    return convertToPinyinArray(c, WITH_TONE_MARK);
}

QString PinyinHelper::convertToPinyinString(const QString &s, const QString &separator, Format pinyinFormat)
{
    const QString &str = m_chineseHelper.convertToSimplifiedChinese(s);
    QString sb;
    for(int i=0, len=str.length(); i<len; i++)
    {
        const QChar &c = str[i];
        if(m_chineseHelper.isChinese(c)/* || c == CHINESE_LING*/)
        {
            bool isFoundFlag = false;
            const int rightMove = 3;

            for(int rightIndex=(i + rightMove) < len ? (i + rightMove) : (len - 1); rightIndex>i; rightIndex--)
            {
                const QString &cizu = str.mid(i, rightIndex + 1);
                if(m_mutliPinyinTable.keys().indexOf(cizu) != -1)
                {
                    const QStringList &pinyinArray = formatPinyin(m_mutliPinyinTable.value(cizu), pinyinFormat);
                    for(int j=0, l=pinyinArray.length(); j<l; j++)
                    {
                        sb.append(pinyinArray[j]);
                        if (j<l - 1)
                        {
                            sb.append(separator);
                        }
                    }
                    i = rightIndex;
                    isFoundFlag = true;
                    break;
                }
            }

            if(!isFoundFlag)
            {
                const QStringList &pinyinArray = convertToPinyinArray(str[i], pinyinFormat);
                if(!pinyinArray.isEmpty())
                {
                    sb.append(pinyinArray[0]);
                }
                else
                {
                    sb.append(str[i]);
                }
            }
            if(i < len - 1)
            {
                sb.append(separator);
            }
        }
        else
        {
            sb.append(c);
            if((i + 1) < len && m_chineseHelper.isChinese(str[i + 1]))
            {
                sb.append(separator);
            }
        }

    }
    return sb;
}

QString PinyinHelper::convertToPinyinString(const QString &str, const QString &separator)
{
    return convertToPinyinString(str, separator, WITH_TONE_MARK);
}

bool PinyinHelper::hasMultiPinyin(char c)
{
    const QStringList &pinyinArray = convertToPinyinArray(c);
    if(!pinyinArray.isEmpty() && pinyinArray.length() > 1)
    {
        return true;
    }
    return false;
}

QStringList PinyinHelper::formatPinyin(QString pinyinString, Format pinyinFormat)
{
    switch(pinyinFormat)
    {
        case WITH_TONE_MARK: return convertWithToneMark(pinyinString);
        case WITH_TONE_NUMBER: return convertWithToneNumber(pinyinString);
        case WITHOUT_TONE: return convertWithoutTone(pinyinString);
        default: return QStringList();
    }
}

QStringList PinyinHelper::convertToPinyinArray(const QChar &c, Format pinyinFormat)
{
    const QString &pinyin = m_pinyinTable.value(QString(c));
    if(!pinyin.isEmpty())
    {
        return formatPinyin(pinyin, pinyinFormat);
    }
    return QStringList();
}

QStringList PinyinHelper::convertWithToneMark(const QString &pinyinArrayString)
{
    return pinyinArrayString.split(m_pinyinSeparator);
}

QStringList PinyinHelper::convertWithToneNumber(const QString &pinyinArrayString)
{
    QStringList pinyinArray = pinyinArrayString.split(m_pinyinSeparator);
    for(int i=pinyinArray.length() - 1; i>=0; i--)
    {
        bool hasMarkedChar = false;
        QString originalPinyin = pinyinArray[i].replace("ü", "v");

        for(int j = originalPinyin.length() - 1; j >= 0; j--)
        {
            QChar originalChar = originalPinyin[j];
            if(originalChar < 'a' || originalChar > 'z')
            {
                int indexInAllMarked = m_allMarkedVowel.indexOf(originalChar);
                int toneNumber = indexInAllMarked % 4 + 1;
                QChar replaceChar = m_allUnmarkedVowel.at(((indexInAllMarked - indexInAllMarked % 4)) / 4);
                pinyinArray[i] = originalPinyin.replace(QString(originalChar), QString(replaceChar)) + QString::number(toneNumber);
                hasMarkedChar = true;
                break;
            }
        }
        if(!hasMarkedChar)
        {
            pinyinArray[i] = originalPinyin + "5";
        }
    }

    return pinyinArray;
}

QStringList PinyinHelper::convertWithoutTone(QString pinyinArrayString)
{
    QStringList pinyinArray;
    for(int i = m_allMarkedVowel.length() - 1; i>=0; i--)
    {
        QChar originalChar = m_allMarkedVowel.at(i);
        QChar replaceChar = m_allUnmarkedVowel.at(((i - i % 4)) / 4);
        pinyinArrayString = pinyinArrayString.replace(QString(originalChar), QString(replaceChar));
    }
    pinyinArray = pinyinArrayString.replace("ü", "v").split(m_pinyinSeparator);

    QSet<QString> pinyinSet;
    foreach(const QString &pinyin, pinyinArray)
    {
        pinyinSet.insert(pinyin);
    }

    return pinyinSet.toList();
}
