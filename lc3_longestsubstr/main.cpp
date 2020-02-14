/**
 *  \brief lc3 Longest Substring Without Repeating Characters
 * 
 *  medium level.
 *  Given a string, find the length of the longest substring without repeating characters.
 *  Consider sliding window to solve.
 *  \author smh
 *  \date 2020.02.14
 */
#include <iostream>
#include <algorithm>

using namespace std;

// baseline: use a map to store the repeated character index; 4ms, 9.3MB; 99.37%, 89.55%
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() <= 1)
            return s.length();
        int char2idx[128];
        for (int i = 0; i < 128; ++i)
            char2idx[i] = -1;
        int curr_len = 0;
        int max_len = 1;
        for (int i = 0; i < s.length(); ++i)
        {
            char c = s.at(i);
            // never seen this character
            if(char2idx[c] < 0)
            {
                ++curr_len;
            }
            // process repeat character
            else
            {
                // compare to last max len
                if (curr_len > max_len)
                {
                    max_len = curr_len;
                }
                if(curr_len >= i - char2idx[c])
                {
                    // update curr_len
                    curr_len = i - char2idx[c];
                }
                else
                {
                    ++curr_len;
                }
            }
            char2idx[c] = i;
        }
        if (curr_len > max_len)
            max_len = curr_len;

        return max_len;
    }
};


// use sliding window: 4ms, 9.2MB, 99.37%, 94.53%
class Solution2
{
public:
    int lengthOfLongestSubstring(string s) {
        int win_start = 0, win_end = 0, win_size = 1;
        int char2idx[128];
        for (int i = 0; i < 128; ++i)
            char2idx[i] = 0;

        while(win_end < s.length())
        {
            // update win_end
            if(char2idx[s[win_end]] == 0)
            {
                ++char2idx[s[win_end]];
                ++win_end;
                win_size = max(win_size, win_end - win_start);
            }
            // update win_start
            else
            {
                --char2idx[s[win_start]];
                ++win_start;
            }
        }

        return win_size;
    }
};

int main()
{
    string in_str = "abcabcbb";
    // string in_str = "abba";
    // string in_str = "tmmzuxt";

    Solution2 sl;
    int res = sl.lengthOfLongestSubstring(in_str);
    cout << "Result: " << res << endl;

    return 0;
}
