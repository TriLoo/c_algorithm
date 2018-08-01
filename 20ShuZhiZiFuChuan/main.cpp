/**
 * \file main.cpp
 *
 * \brief 剑指Offer第20题
 *
 * \brief 主要思路是，确定字符串构成一个数值的所有的样式：[+-A][.B][e|EC], 剩下的就是操纵字符串来看看是否满足这个样式
 */
#include <iostream>

using namespace std;


bool isUnsignedInteger(string &s, int & idx)
{
    int startIdx = idx;
    int len = s.length();
    while (idx < len && s.at(idx) >= '0' && s.at(idx) <= '9')
        ++idx;

    return startIdx < idx;
}

bool isInteger(string &s, int& idx)
{
    if (s.at(idx) == '+' || s.at(idx) == '-')
        ++idx;

    return isUnsignedInteger(s, idx);
}

//! \brief 如果是一个数字，需要具备以下样式：[+-A][.B][e|EC]
bool isNum(string &sin)
{
    if (sin.length() == 0)
        return false;

    int idx = 0;

    // 首先扫描A之前的部分
    bool critical = isInteger(sin, idx);

    if (idx == sin.length())
        return critical;

    // 判断是否是B模式
    if (sin.at(idx) == '.')
    {
        ++idx;
        critical = isUnsignedInteger(sin, idx) || critical;
    }

    if (idx == sin.length())
        return critical;

    // 判断是否是C模式
    if (sin.at(idx) == 'e' || sin.at(idx) == 'E')
    {
        ++idx;
        critical = critical && isInteger(sin, idx);
    }

    return critical;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    string s1;
    cin >> s1;

    cout << isNum(s1) << endl;

    return 0;
}
