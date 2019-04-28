#include "shiftjis.h"

#include <vector>

#define ShiftJIS_one_byte_func(a, b) \
    [](const unsigned char *s) \
    { \
        return *s >=a && *s <= b; \
    }

#define ShiftJIS_two_byte_func(a, b, c, d) \
    [](const unsigned char *s) \
    { \
        return *s >=a && * s<= b && s[1] >= c && s[1] <= d; \
    }

const vector<pair<int, function<bool(const unsigned char*) > > > ShiftJIS_Detect = {
        {2, ShiftJIS_two_byte_func(0x40, 0x7E, 0x80, 0xFC)},
        {2, ShiftJIS_two_byte_func(0x81, 0x9F, 0xE0, 0xEF)},
        {1, ShiftJIS_one_byte_func(0x00, 0x7F)},
        {1, ShiftJIS_one_byte_func(0xA1, 0xDF)} };

ShiftJISChecker::ShiftJISChecker()
    : CheckerBase("shift_jis")
{

}

bool ShiftJISChecker::detect(const string &str) const
{
    int index = -1;
    int length = str.length();
    const unsigned char* buffer = (const unsigned char*)str.c_str();
    while(index + 1 < length)
    {
        bool flag = false;
        int leftLength = length - index - 1;
        for(auto func : ShiftJIS_Detect)
        {
            if(func.first >= leftLength && func.second(buffer))
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
