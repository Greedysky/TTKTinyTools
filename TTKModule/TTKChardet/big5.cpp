#include "big5.h"

#include <vector>

#define Big5_two_byte_func(min, max) \
    [](const unsigned char *s) \
    { \
        unsigned short value = (*s << 8) + s[1]; \
        return value >= min && value <= max; \
    }

const vector< function< bool(const unsigned char*) > > Big5_Detect = {
        Big5_two_byte_func(0xa140, 0xa3bf),
        Big5_two_byte_func(0xa440, 0xc67e),
        Big5_two_byte_func(0xc940, 0xf9d5) };

Big5Checker::Big5Checker()
    : CheckerBase("big5")
{

}

bool Big5Checker::detect(const string &str) const
{
    int index = -1;
    int length = str.length();
    const unsigned char *buffer = (const unsigned char*)str.c_str();
    while(index + 1 < length)
    {
        if(*buffer <= 0x7F)
        {
            index += 1;
            buffer += 1;
        }

        if(checkTwoBytes(buffer))
        {
            index += 2;
            buffer += 2;
        }
        else
        {
            break;
        }
    }
    return (index + 1 == length);
}

bool Big5Checker::checkTwoBytes(const unsigned char *buffer) const
{
    for(auto func : Big5_Detect)
    {
        if(func(buffer))
        {
            return true;
        }
    }
    return false;
}
