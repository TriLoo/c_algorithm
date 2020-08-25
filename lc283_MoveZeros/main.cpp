/**
 * \brief lc283 Moving Zeros
 * 
 *  level Easy.
 *  Given an array `nums`, write a func to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
 * 
 * \file main.cpp
 * \date 2020.08.25
 */

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    /// solution 1: bruce force, move every zero to the end, -> O(n^2)
    /// solution 2: one pointer record current non-zero position, copy another element to here
    void moveZeroes(vector<int>& nums) 
    {
        // int left = 0, right = 1;
        int left = 0;
        while (left < nums.size())
        {
            if (nums[left] != 0)
            {
                ++left;
                continue;
            }
            int right = left + 1;
            // find the next non-zero element
            while(right < nums.size() && nums[right] == 0)
                ++right;
            if (right == nums.size())
                break;
            std::swap(nums[right], nums[left]);
        }
    }
    /// solution 3: two pointers
    void moveZeros_2(vector<int>& nums)
    {
        int left = 0, right = 1;
        while(left < nums.size())
        {
            if (nums[left])
            {
                ++left;
                ++right;
                continue;
            }
            while(right < nums.size() && nums[right] == 0)
                ++right;
            if (right == nums.size())
                break;
            std::swap(nums[right], nums[left]);
        }
    }
    /// solution 4: two pointers, cannot process well cases which much leading zeros exists, e.g. [0, 0, ...., 0, 1] -> write n-1 times zero to the end
    void moveZeros_3(vector<int>& nums)
    {
        int left = 0, right = 0;
        for (; right < nums.size(); ++right)
        {
            if (nums[right])
                nums[left++] = nums[right];
        }
        for(int i = left; i < nums.size(); ++i)
            nums[i] = 0;
    }
    /// solution 5: drop the second for in solution 4
    void moveZeros_4(vector<int>& nums)
    {
        int left = 0, right = 0;            // right point to the current non-zero position
        for(; right < nums.size(); ++right)
        {
            if (nums[right])
                std::swap(nums[left++], nums[right]);
        }
    }
};


int main()
{
    vector<int> nums = {0,1,0,3,12};
    Solution sl;
    // sl.moveZeroes(nums);
    // sl.moveZeros_2(nums);
    // sl.moveZeros_3(nums);
    sl.moveZeros_4(nums);

    for (auto elem : nums)
        cout << elem << endl;

    return 0;
}
