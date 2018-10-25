/**
 * @author smh
 * @date 2018.10.24
 *
 * @brief Leetcode 14 Easy
 *   Longest Common Prefix
 *
 *   Note:
 */
#include <iostream>
#include <vector>

using namespace std;

string getLCP(string s1, string s2)
{
    int len1 = s1.length(), len2 = s2.length();

    len1 = len1 < len2 ? len1 : len2;
    string ret;

    for (int i = 0; i < len1; ++i)
    {
        if(s1.at(i) == s2.at(i))
            ret.push_back(s1.at(i));
        else
            break;
    }

    return ret;
}

// Approach 1: Horizontal scanning
// Time complexity: O(S), S is the sum of all characters in all strings
// Space complexity: O(1)
string longestCommonPrefix(vector<string> &strs)
{
    if(strs.empty())
        return "";

    string ret = strs.front();

    for (auto &ele : strs)
    {
        ret = getLCP(ret, ele);
        if(ret.length() == 0)
            break;
    }

    return ret;
}

int main() {
    // Under test


    return 0;
}
