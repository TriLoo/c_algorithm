/**
 * @author smh
 * @date 2018.10.25
 *
 * @brief Leetcode 15 Medium
 *   3 Sum: Find all unique triplets in the array which gives the sum of zero.
 *
 *   Notes:
 *      参考： https://leetcode.com/problems/3sum/discuss/181595/c++-short-simple-solution.-With-description-and-reasoning.
 *     具体的做法是基于2Sum的思想来做，就是先固定一个数值，然后剩下的两个数值以2Sum的方式来确定.
 *     2Sum问题的解决： 输入为一个有序数组、目标值
 *         准备两个索引(lower, upper)，初始化为分别指向vector的首元素、尾元素，然后这两个元素的和分成3种情况：
 *         1. lower + upper 大于目标值，此时需要降低upper的索引
 *         2. lower + upper 小于目标值，此时需要增加lower的索引
 *         3. lower + upper 等于目标值，此时索引对就是一个可行解
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int> &nums)
{
    if(nums.size() < 3)
        return vector<vector<int>>();

    vector<vector<int>> ret;
    sort(nums.begin(), nums.end()); // 从小到大

    vector<int> solves;

    // 这么做的原因是： 相当于每次迭代都把当前值当做三个数值中的最小值的候选，因为是枚举，所以是可以的
    for (int i = 0; i+2 < nums.size(); ++i)
    {
        if(i && (nums.at(i-1) == nums.at(i)))   // 避免重复计算，因为nums.at(i)被当做target值， 并作为最小值
            continue;

        int target = -1 * nums.at(i);
        int lower = i+1, upper = nums.size() - 1;
        while(lower < upper)
        {
            solves.clear();
            if(target > nums.at(lower) + nums.at(upper))
                ++lower;
            else if(target < nums.at(lower) + nums.at(upper))
                --upper;
            else
            {
                solves.push_back(nums.at(i));
                solves.push_back(nums.at(lower));
                solves.push_back(nums.at(upper));
                ret.push_back(solves);

                // 保证不使用重复的数字
                do
                {
                    ++lower;
                }while (lower < upper && nums.at(lower - 1) == nums.at(lower));
            }

        }
    }

    return ret;
}

int main() {
    // Under test

    return 0;
}
