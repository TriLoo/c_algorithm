/**
 * @author smh
 * @date 2018.10.13
 *
 * @brief Leetcode10 Hard
 *   Regular Expression Matching
 *
 *   Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
 *
 *   Notes: Use Dynamic Programming
 */
#include <iostream>
#include <vector>

using namespace std;

bool isMatch(string s, string p)
{
    if(p.front() == '*')
        return false;

    int m = s.length(), n = p.length();
    // dp第(i, j)个元素表示：s的前i个元素与p的前j个元素是匹配的
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));   // 每个元素是vector<bool>(n+1, false)，默认值全为false
    dp[0][0] = true;
    for (int i = 0; i <= m; ++i)
    {
        for (int j = 1; j <= n ; ++j)
        {
            if(p[j-1] == '*')
                dp[i][j] = dp[i][j-2] || (i > 0 && (s[i-1] == p[j-2] || p[j-2] == '.') && dp[i-1][j]);
            else
                dp[i][j] = i > 0 && dp[i - 1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
        }
    }

    return dp[m][n];
}

int main()
{
}

/*
bool isMatch(string s, string p)
{
    int len1 = s.length(), len2 = p.length();

    if(len2 == 0)
        return len1 == 0;

    int i = 0, j = 0;
    bool ret = true;

    if(p.at(0) == '*')
        return false;

    while(j < len2)
    {
        if(i == len1)
        {
            ret = false;
            break;
        }

        if((s.at(i) == p.at(j)) || (p.at(j) == '.'))
        {
            ++i;
            ++j;
        }

        if(p.at(j) == '*')
        {
            char c = p.at(j-1);

            while(s.at(i++) == c)
            {
                if(j == len2-1)
                    return true;

                if(i == len1)
                    return false;
            }

            ++j;
        }
    }

    return ret;
}

int main() {
    string s, p;
    cin >> s >> p;

    if(isMatch(s, p))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}
*/
