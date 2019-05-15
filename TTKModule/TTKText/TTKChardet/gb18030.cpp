#include "gb18030.h"

#include <vector>

#define GB18030_two_byte_func(a, b, c, d) \
    [](const unsigned char *s) \
    { \
        return *s >= a && *s <= b && s[1] >= c && s[1] <= d; \
    }

#define GB18030_four_byte_func(min, max) \
    [](const unsigned char *s) \
    { \
        return GB18030_two_byte_func(0x81, 0x82, 0x30, 0x39)(s) && \
               GB18030_two_byte_func(0x81, 0xFE, 0x30, 0x39)(s + 2); \
    }

const vector< pair <int, function<bool(const unsigned char*)> > > GB18030_Detect = {
        {1, [](const unsigned char *s){ return *s <= 0x7F;} },
        {2, GB18030_two_byte_func(0xB0, 0xF7, 0xA1, 0xFE)},
        {2, GB18030_two_byte_func(0x81, 0xA0, 0x40, 0xFE)},
        {2, GB18030_two_byte_func(0xAA, 0xFE, 0x40, 0xA0)},
        {4, GB18030_four_byte_func(0x81, 0x82)},
        {4, GB18030_four_byte_func(0x95, 0x98)} };


GB18030Checker::GB18030Checker()
    : CheckerBase("gb18030")
{

}

bool GB18030Checker::detect(const string &str) const
{
    int index = -1;
    int length = str.length();
    const unsigned char* buffer = (const unsigned char*)str.c_str();
    while(index + 1 < length)
    {
        bool flag = false;
        int leftLength = length - index - 1;
        for(auto func : GB18030_Detect)
        {
            if(func.first <= leftLength && func.second(buffer))
            {
                index += func.first;
                buffer += func.first;
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
