#include "iso2022_jp.h"

#include <map>
#include <string.h>

const map<string, ISO2022_jp_pair> ISO2022_Detect = {
    {("\x1b(B"), {1, [](const unsigned char *) { return true; }}},
    {("\x1b(J"), {1, [](const unsigned char *) { return true; }}},
    {("\x1b$@"), {2, [](const unsigned char *) { return true; }}},
    {("\x1b$B"), {2, [](const unsigned char *) { return true; }}} };

ISO2022_JPChecker::ISO2022_JPChecker()
    : CheckerBase("iso2022_jp")
{

}

bool ISO2022_JPChecker::detect(const string &str) const
{
    const char *buffer = str.c_str();
    ISO2022_jp_pair func = {1, [](const unsigned char *s){ return *s <= 0x7F; }};
    while(strlen(buffer))
    {
        auto result = checkFlag(buffer);
        if(get<0>(result))
        {
            func = get<1>(result);
        }
        else
        {
            if(func.second((const unsigned char *)buffer))
            {
                buffer += func.first;
            }
            else
            {
                break;
            }
        }
    }
    return (strlen(buffer) == 0);
}

tuple<bool, ISO2022_jp_pair> ISO2022_JPChecker::checkFlag(const char *&str) const
{
    tuple<bool, ISO2022_jp_pair> ret = make_tuple(false, ISO2022_jp_pair());
    for(auto &func : ISO2022_Detect)
    {
        string flag = func.first;
        if(!strncmp(flag.c_str(), (const char *)str, flag.size()))
        {
            str += flag.size();
            ret = make_tuple(true, func.second);
            break;
        }
    }
    return ret;
}
