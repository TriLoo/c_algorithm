/**
 * @author smh
 * @date 2018.08.23
 *
 * @brief 剑指offer第67题
 *   把字符串转换成整数
 *
 *   思路：
 *      1. 需要考虑的情况：
 *          A. 正负号
 *          B. 输入是否包含字符
 *          C. 全局状态量
 */
#include <iostream>

using namespace std;

enum Statue
{
    kValid=0,
    kInValid
};

int g_status = kInValid;

int convertString2int(string s)
{
    int len = s.length();
    if (len == 0)
    {
        g_status = kInValid;
        return 0;
    }

    int idx = 0;
    int mins_flag = 0;
    if(s.at(0) == '+')
    {
        ++idx;
        mins_flag = 0;
    }
    else
    {
        ++idx;
        mins_flag = 1;
    }

    int num = 0;
    for (; idx < len; ++idx)
    {
        if (s.at(idx) <= '9' && s.at(idx) >= '0')
            num = 10 * num + (s.at(idx) - '0');
        else
        {
            num = 0;
            g_status = kInValid;
            break;
        }
    }

    if (idx == len)
    {
        g_status = kValid;
        if (mins_flag)
            num = 0 - num;
    }

    return num;
}

int main() {
    string s;
    cin >> s;
    cout << convertString2int(s) << endl;

    return 0;
}
