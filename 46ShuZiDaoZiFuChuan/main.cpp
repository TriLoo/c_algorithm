/**
 * @author smh
 * @date 2018.08.19
 *
 * @brief 剑指offer第46题
 *   把数字翻译成字符串
 *
 *   思路：
 *      1. 动态规划，定义状态为f(i)为从左边到第i位可能组成的状态个数；状态转移就是前一位 + 可能的前两位
 */
#include <iostream>

using namespace std;

int getPossibleNum(string s1)
{
    int len = s1.length();
    int *count = new int [len]();

    for (int i = len-1; i >= 0; --i)
    {
        int c = 0;
        if (i < len-1)
            c = count[i+1];
        else
            c = 1;

        if (i < len-1)
        {
            int d1 = s1[i] - '0';
            int d2 = s1[i+1] - '0';
            int cmb = d1 * 10 + d2;
            if (cmb >= 10 && cmb <= 25)
            {
                if (i < len - 2)
                    c += count[i+2];
                else
                    c += 1;
            }
        }
        count[i] = c;
    }

    int a = count[0];
    delete [] count;

    return a;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int a;
    cin >> a;
    string s1 = to_string(a);
    cout << getPossibleNum(s1) << endl;

    return 0;
}
