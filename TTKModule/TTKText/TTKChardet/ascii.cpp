#include "ascii.h"

AsciiChecker::AsciiChecker()
    : CheckerBase("ascii")
{

}

bool AsciiChecker::detect(const string &str) const
{
    for(unsigned char ch : str)
    {
        if(ch >> 7) // whether the first bit is 1
        {
            return false;
        }
    }
    return true;
}
