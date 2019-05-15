#include "checkerhelper.h"

#include <algorithm>

#include "ascii.h"
#include "big5.h"
#include "gb18030.h"
#include "gbk.h"
#include "iso2022_jp.h"
#include "shiftjis.h"
#include "utf8.h"

CheckerHelper::CheckerHelper()
{
    m_checkers.insert(make_pair("ascii", new AsciiChecker));
    m_checkers.insert(make_pair("big5", new Big5Checker));
    m_checkers.insert(make_pair("gb18030", new GB18030Checker));
    m_checkers.insert(make_pair("gbk", new GBKChecker));
    m_checkers.insert(make_pair("iso2022_jp", new ISO2022_JPChecker));
    m_checkers.insert(make_pair("shift_jis", new ShiftJISChecker));
    m_checkers.insert(make_pair("utf8", new UTF8Checker));
}

CheckerHelper::~CheckerHelper()
{
    for(auto &func : m_checkers)
    {
        delete func.second;
    }
}

CheckerBase* CheckerHelper::getChecker(const string &name)
{
    auto it = m_checkers.find(name);
    if(it == m_checkers.end())
    {
        return nullptr;
    }
    else
    {
        return it->second;
    }
}

bool CheckerHelper::contains(const string &name)
{
    auto it = m_checkers.find(name);
    return it != m_checkers.end();
}

bool CheckerHelper::check(const string &charset, const string &str)
{
    string in(charset);
    std::transform(in.begin(), in.end(), in.begin(), ::tolower);

    if(contains(in))
    {
        return getChecker(in)->detect(str);
    }
    return false;
}

string CheckerHelper::detect(const string &str)
{
    string charSet = "unknown";
    for(const auto& checker: m_checkers)
    {
        if(checker.second->detect(str))
        {
            charSet = checker.first;
            break;
        }
    }
    return charSet;
}
