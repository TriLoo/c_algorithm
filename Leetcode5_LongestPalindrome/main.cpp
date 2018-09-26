/**
 * @author smh
 * @date 2018.09.25
 *
 * @brief Leetcode 5 medium
 *   Longest palindromic substring
 *
 *   思路：
 *      Approach 2: Brute Force O(n^3)
 *          检测每一个可能的子字符串，每个子字符串判断一次的复杂度是O(n)，因此共是O(n^3),space complexity O(1)
 *
 *      Approach 3: Dynamic Programming O(n^2),space complexity O(n^2)
 *          更新规则： P(i, j) = (P(i+1, j-1) and S_i == S_j); S_i为第i个字符
 *          Base Cases:
 *                  P(i, i) = true
 *                  P(i, i+1) = (S_i == S_{i+1})
 *
 *      Approach 4: Expand Around Center
 *          时间复杂度为O(n^2), 空间复杂度为常量
 *
 *          A palindrome can be expanded from its center, and there are only 2n-1 such centers. (因为也需要考虑中心在两个字符中间的情况)
 *          这种途径的主要思想是，对于每一个可能的扩展中心，计算以该点为中心时的回文长度，并不断更新当前的最大长度
 */
#include <iostream>

using namespace std;

// Approach 3: DP
// Not Tested.
string longestPalindrome3(string s)
{
    int len = s.length();
    // 纵轴表示开始位置，列轴表示结束位置
    int **tables = new int* [len];
    for (int i = 0; i < len; ++i)
        tables[i] = new int [len];

    int start = 0, end = 0;

    for(int i = 0; i < len; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            // Base cases
            if(j < i)
            {
                tables[i][j] = 0;
                continue;
            }
            if(i == j)
            {
                tables[i][j] = 1;
                continue;
            }
            if((i == 0) || (j == 0))
            {
                tables[i][j] = 1;
                continue;
            }
            if(i == len-1 || j == len-1)
            {
                tables[i][j] = 1;
                continue;
            }

            // 后续就是更新规则了
        }
    }

    for (int i = 0; i < len; ++i)
        delete [] tables[i];
    delete [] tables;

    return s.substr(start, end - start);
}

// Approach 4: expand around center
// 空间复杂度为O(1)，因为是在原来字符串上面进行计算的
int expandLength(string& s, int L, int R);
string longestPalindrome4(string s)
{
    if (s.length() < 1)
        return "";
    int len = s.length();
    int start = 0, end = 0;                  // 初始时默认只有长度为一的情况存在，并且就是最开始的这个字符
    int currLen = 0;
    for (int i = 0; i < len; ++i)            // 每个元素其实对应的接近2个中心，除了最后一个元素只有它自己
    {
        int len1 = expandLength(s, i, i);    // 此时等价于第i个元素为扩展中心!
        int len2 = expandLength(s, i, i+1);  // 此时等价于第i个元素与第i+1个元素之间的中心为扩展中心
        currLen = max(len1, len2);       // 注意，两种不同的中心的情况下最长长度可能不同！毕竟要分偶数个字符和奇数个字符
        if(currLen > end - start)            // 更新最长的回文子字符串
        {
            start = i - (currLen - 1) / 2;   // 回文子字符串左边的边界索引，左边索引相当于少见去了0.5，这是因为在计算len2中，是以左边的索引来衡量的，因此需要减去0.5,
                                             // 若中心位于两个字符中间，这等价于减去1；若中心位于当前字符，这等价于没有作用。
            end = i + currLen / 2;           // 回文子字符串右边的边界索引，
        }
    }

    return s.substr(start, end-start+1);             // 返回最长子字符串, substr(pos, len)
}

int expandLength(string& s, int L, int R)
{
    while (L >= 0 && R < s.length() && (s.at(L) == s.at(R)))
    {
        --L;
        ++R;
    }

    return R - L - 1;   // -1 是因为L和R包含了回文子字符串，本来应该是最长字符串最右边索引减去最左边索引并+1的，现在相当于多加了1，因此这里需要减去1
                        // 例如：字符串的索引是： 2-4,也就是长度为3，而现在L和R分别是1和5了，因此，还需要-1
}

int main() {
    string s;
    cin >> s;
    cout << longestPalindrome4(s) << endl;

    return 0;
}
