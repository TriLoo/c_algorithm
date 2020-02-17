/**
 *  \brief lc4 Median of Two Sorted Array
 * 
 *  level hard.
 *  There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *  Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 *  You may assume nums1 and nums2 cannot be both empty.
 *  
 *  \author smh
 *  \date 2020.02.15
 */
#include <iostream>
#include <vector>

using namespace std;

// baseline: merge sort, 24ms, 9.6MB, faster than 45.38 %, less than 96.91 %
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int num1_sz = nums1.size(), num2_sz = nums2.size();
        int prev = 0, curr = 0;
        int right = 0, left = 0;
        for(int i = 0; i <= (num1_sz + num2_sz) / 2; ++i)
        {
            prev = curr;
            // update left
            if((right >= num1_sz) || ((left < num2_sz) && (nums2[left] < nums1[right])))
                curr = nums2[left++];
            else
                curr = nums1[right++];
        }
        if ((num1_sz + num2_sz) & 0x01)
            return curr;
        else
            return (prev + curr) / 2.0;
    }
};

// use binary, not understand yet
class Solution2
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

    }
};

int main()
{
    // vector<int> a = {1, 2};
    // vector<int> b = {3, 4};
    vector<int> a = {1, 3};
    vector<int> b = {2};

    Solution sl;
    auto res = sl.findMedianSortedArrays(a, b);

    cout << "res = " << res << endl;

    return 0;
}
