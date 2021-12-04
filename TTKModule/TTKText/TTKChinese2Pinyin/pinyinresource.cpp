#include "pinyinresource.h"

#include <QFile>
#include <QTextStream>

TTKStringMap PinyinResource::pinyinResource()
{
    return resource(":/data/pinyin");
}

TTKStringMap PinyinResource::mutilPinyinResource()
{
    return resource(":/data/mutil_pinyin");
}

TTKStringMap PinyinResource::chineseResource()
{
    return resource(":/data/single_pinyin");
}

TTKStringMap PinyinResource::resource(const QString &resourceName)
{
    TTKStringMap map;
    QFile file(resourceName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return map;
    }

    QTextStream in(&file);
#if TTK_QT_VERSION_CHECK(6,0,0)
    in.setEncoding(QStringConverter::Utf8);
#else
    in.setCodec("utf-8");
#endif

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
