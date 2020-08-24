/**
 * \brief lc26 Remove Duplicate from Sorted Array
 * 
 *  level Easy.
 *  Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.
 *  Do not allocate extra space for other array, you must do this by modifying the input array in-place with O(1) extra memory.
 * 
 * \file main.cpp
 * \date 2020.08.24
 */

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    /// use the std::unique()
    int removeDuplicates(vector<int>& nums) {
        // int i = 0, j = 1;
        auto beg = unique(nums.begin(), nums.end());
        nums.erase(beg, nums.end());
        return nums.size();
    }
    /// use self-implemented unique func
    int removeDuplicates_2(vector<int>& nums) 
    {
        if (nums.size() == 0)
            return 0;

        auto beg = nums.begin(), end = nums.end();
        auto res = beg;
        while(++beg != end)
        {
            if ((*res != *beg) && (++res != beg))
                *res = std::move(*beg);
        }
        ++res;
        return std::distance(nums.begin(), res);
    }
};


int main()
{
    // vector<int> nums = {1, 1, 2};
    vector<int> nums = {0,0,1,1,1,2,2,3,3,4};
    Solution sl;
    // int res = sl.removeDuplicates(nums);
    int res = sl.removeDuplicates_2(nums);

    cout << "Result: " << endl;
    cout << res << endl;
    cout << "------------" << endl;
    for (auto & elem : nums)
        cout << elem << endl;

    return 0;
}
