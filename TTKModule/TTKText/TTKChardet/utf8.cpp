#include "utf8.h"

#include <map>

bool bytesExtraCheck(const unsigned char* str, int length)
{
    for(int i=0; i<length; ++i)
    {
        if((str[i] & 0xC0) != 0x80)
        {
            return false;
        }
    }
    return true;
}

#define multibyte_utf8(a, b, num) \
    [](const unsigned char *s, int len) \
    { \
        return ((*s)&a) == b && len >= num && bytesExtraCheck(s + 1, num - 1); \
    }

const map<int, function<bool(const unsigned char *, int) > >UTF8_Detect = {
                        {1, multibyte_utf8(0x80, 0x00, 1)},
                        {2, multibyte_utf8(0xE0, 0xC0, 2)},
                        {3, multibyte_utf8(0xF0, 0xE0, 3)},
                        {4, multibyte_utf8(0xF8, 0xF0, 4)},
                        {5, multibyte_utf8(0xFC, 0xF8, 5)},
                        {6, multibyte_utf8(0xFE, 0xFC, 6)} };

UTF8Checker::UTF8Checker()
    : CheckerBase("utf-8")
{

}

bool UTF8Checker::detect(const string &str) const
{
    int index = -1 ;
    int length = str.length();
    const unsigned char *buffer = (const unsigned char*)str.c_str();
    while(index + 1 < length)
    {
        bool flag = false;
        for(auto &func : UTF8_Detect)
        {
            if(func.second(buffer, length - index - 1))
            {
                buffer += func.first;
                index += func.first;
                flag = true;
                break;
            }
        }

        if(!flag)
        {
            break;
        }
    }
    return (index + 1 == length);
}
