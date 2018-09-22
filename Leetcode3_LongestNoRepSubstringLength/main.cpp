/**
 * @author smh
 * @date 2018.09.22
 *
 * @brief Leetcode 3 medium
 *   Longest substring without repeating characters.
 *
 *   Given a string, find the length of the longest substring without repeating characters.
 *
 *   思路： ASCII characters 共有128个，要做的是以一个hashmap，key为字符，可以用整数代替；value是出现的位置索引
 *          基于动态规划思想，也就是说，对每个新位置判断如何更新最长不重复字符串。
 *          若当前字符已经出现过，则计算距离上次出现的间隔，与当前最大不重复字符串长度比较，若大于后者则当前最大字符串长度更新为+1,同时
 *          更新全局最大不重复字符串长度;
 *          若小于后者，则仅更新hashmap中的value，以及当前最大不重复字符串长度。
 */

#include <iostream>
#include <vector>

using namespace std;

int lengthOfLongestSubstring(string s)
{
    vector<int> charIdx(128, -1);   // 初始值为-1
    int len = s.length();
    if(len == 0)
        return 0;

    int maxLen = 0;
    int currLen = 0;
    for (int i = 0; i < len; ++i)
    {
        char c = s.at(i);
        int idx = charIdx.at(static_cast<int>(c));

        if(idx == -1)
        {
            ++currLen;
            if(currLen > maxLen)
                maxLen = currLen;
            charIdx.at(static_cast<int>(c)) = i;
            continue;
        }

        if(i - idx > currLen)
        {
            ++currLen;
            if(currLen > maxLen)
                maxLen = currLen;
            charIdx.at(static_cast<int>(c)) = i;
        }
        else
        {
            currLen = i - idx;
            charIdx.at(static_cast<int>(c)) = i;
        }
    }

    return maxLen;
}

int main() {
    // under test
    cout << static_cast<int>('1') << endl;   // 49

    return 0;
}