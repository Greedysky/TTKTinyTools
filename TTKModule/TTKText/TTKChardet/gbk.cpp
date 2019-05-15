#include "gbk.h"

GBKChecker::GBKChecker()
    : CheckerBase("gbk")
{

}

bool GBKChecker::detect(const string &str) const
{
    int index = -1;
    int length = str.length();
    const unsigned char* buffer = (const unsigned char*)str.c_str();
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

bool GBKChecker::checkTwoBytes(const unsigned char *buffer) const
{
    bool fValid = (*buffer >= 0x81 && *buffer <= 0xFE);
    ++buffer;
    bool sValid = (*buffer >= 40 && *buffer <= 0xFE && *buffer != 0x7F);
    return fValid && sValid;
}
