#include "pinyinresource.h"

#include <QFile>
#include <QTextStream>

TTKStringMap PinyinResource::getPinyinResource()
{
    return getResource(":/data/pinyin");
}

TTKStringMap PinyinResource::getMutilPinyinResource()
{
    return getResource(":/data/mutil_pinyin");
}

TTKStringMap PinyinResource::getChineseResource()
{
    return getResource(":/data/single_pinyin");
}

TTKStringMap PinyinResource::getResource(const QString &resourceName)
{
    TTKStringMap map;
    QFile file(resourceName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return map;
    }

    QTextStream in(&file);
    in.setCodec("utf-8");

    QString line;
    while((line = in.readLine()) != QString())
    {
        const QStringList &tokens = line.trimmed().split("=");
        if(tokens.count() >= 2)
        {
            map.insert(tokens[0], tokens[1]);
        }
    }

    file.close();
    return map;
}
