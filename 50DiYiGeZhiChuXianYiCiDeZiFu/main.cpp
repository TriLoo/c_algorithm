/**
 * @author smh
 * @date 2018.08.21
 *
 * @brief 剑指offer第50题
 *   第一个只出现一次的字符
 *
 *   思路：
 *      1. 定义一个辅助数组，对应26个不同的字符，其实本质上这是一种hash结果，也就是说：key为位置索引，value为对应的字符，只不过这里不需要
 *         明确地存储字符
 */
#include <iostream>

using namespace std;

char getFirstChar(string &s)
{
    int *flags = new int[256];
    for (int i = 0; i < 256; ++i)
        flags[i] = 0;
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        flags[static_cast<int>(s.at(i))] += 1;
    }

    char c;
    for (int i = 0; i < 256; ++i)
    {
        if (flags[i] == 1)
        {
            c = static_cast<char>(i);
            break;
        }
    }

    delete [] flags;

    return c;
}


int main() {
    string s;
    getline(cin, s);

    cout << getFirstChar(s) << endl;

    return 0;
}
