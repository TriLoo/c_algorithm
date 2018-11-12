/**
 * @author smh
 * @date 2018.11.05
 *
 * @brief Leetcode 16, Medium
 *   3Sum Closest
 *
 *   Return the sum of the three integers that the sum is cloest to 'target'.
 *   Notes:
 *     1.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int threeSumClosest(vector<int>& nums, int target)
{
    if(nums.size() < 3)
        return 0;
    int currRes = 0, currSum = 0.0;
    int currMinRes = INT32_MAX;

    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size(); ++i)
    {
        //currSum += nums.at(i);
        int j = i+1, k = nums.size() - 1;
        while(j < k)
        {
            currRes = target - (nums.at(i) + nums.at(j) + nums.at(k));
            //cout << abs(currRes) << endl;
            if(abs(currRes) < currMinRes)
            {
                currMinRes = abs(currRes);
                currSum = nums.at(i) + nums.at(j) + nums.at(k);
            }
            // 更新索引值, 朝着降低残差的方向努力
            if(currRes < 0)  // should ++j
            {
                --k;
            }
            else if (currRes > 0)
            {
                ++j;
            }
            else   // closest sum is target itself.
                return target;
        }
    }
    return currSum;
}

int main() {
    // Under test
    //vector<int> nums = {-1, 2, 1, -4};
    //int target = 1;
    vector<int> nums = {0, 1, 1, 1};
    int target = -100;

    cout << threeSumClosest(nums, target) << endl;

    return 0;
}
