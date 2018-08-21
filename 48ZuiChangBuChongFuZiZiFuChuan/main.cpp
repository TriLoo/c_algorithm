/**
 * @author smh
 * @date 2018.08.20
 *
 * @brief 剑指offer第48
 *   最长不含重复字符的子字符串
 *
 *   思路：
 *      1. 动态规划，状态f(i)表示第(i)位时最大的不重复子字符串长度、状态的转移是与i-1的状态以及上一次重复的数字有关
 */
#include <iostream>

using  namespace std;

int longestSubString(string s)
{
    if (s.length() == 0)
        return 0;

    int *positions = new int [26];
    for (int i = 0; i < 26; ++i)
        positions[i] = -1;

    int len = s.length();

    int currMax = 0;
    for (int i = 0; i < len; ++i)
    {
        int idx = s.at(i) - 'a';
        if (positions[idx] != -1)
        {
            int d = i - positions[idx];
            if (d > currMax)
                currMax += 1;
            else
                currMax = d;
        }
        else
            currMax += 1;
        positions[idx] = i;
    }

    delete [] positions;

    return currMax;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    string s;
    cin >> s;
    cout << longestSubString(s) << endl;

    return 0;
}
