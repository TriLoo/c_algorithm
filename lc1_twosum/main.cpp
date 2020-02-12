/**
 * \brief leetcode 1
 * 
 *  easy level.
 *  Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 *  You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * 
 *  hint: Use unordered_map !!!
 * 
 * \author smh
 * \date 2020.02.12
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Baseline, O(N^2), 136 ms, 9.3 MB
class Solution{
    public:
        vector<int> twoSum(vector<int> nums, int target)
        {
            for (int i = 0; i < nums.size(); ++i)
                for(int j = i+1; j < nums.size(); ++j)
                {
                    if (nums.at(i) + nums.at(j) == target)
                        return {i, j};
                }
            return {};
        }
};

// Use unordered_map, O(N), 8 ms, 10.4 MB
class Solution2{
    public:
        vector<int> twoSum(vector<int> nums, int target)
        {
            // value -> index
            unordered_map<int, int> val2idx;
            for (int i = 0; i < nums.size(); ++i)
                val2idx[nums[i]] = i;

            for(int i = 0; i < nums.size(); ++i)
            {
                int tmp = target - nums[i];
                if (val2idx.find(tmp) != val2idx.end() && val2idx[tmp] != i)
                    return {i, val2idx[tmp]};
            }

            return {};
        }
};


int main()
{
    Solution2 sl;
    vector<int> nums = {2, 7, 11, 5};
    int target = 9;

    auto res = sl.twoSum(nums, target);
    for (auto l : res)
        cout << l << " " << endl;

    return 0;
}
