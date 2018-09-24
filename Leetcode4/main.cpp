/**
 * @author smh
 * @date 2018.09.23
 *
 * @brief Leetcode 4
 *   Median of Two Sorted Arrays
 *
 *      思路： 根据中位数定义，当元素的个数为奇数时，中位数为中间的数；若元素个数为偶数时，中位数为中间的两个数的均值
 *            针对两个排序的数组，中位数所在的位置，是
 */
#include <iostream>
#include <vector>

using namespace std;


// Complexity: O(log(m+n))
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    if(nums1.size() > nums2.size())
        nums1.swap(nums2);

    int len1 = nums1.size(), len2 = nums2.size(), len = len1 + len2;
    int mid = (len - 1) >> 1;
    int l = 0, r = len1 - 1;
    while(l <= r)    // 找到正好满足nums1[m1] > nums2[mid - m1]的那个m1
    {
        int m1 = l + ((r - l) >> 1);
        int m2 = mid - m1;
        if(nums1.at(m1) > nums2.at(m2))
            r = m1 - 1;
        else
            l = m1 + 1;
    }

    int a = max(r >= 0?nums1.at(r):INT32_MIN, mid-l >= 0 ? nums2.at(mid-l):INT32_MIN);
    if(len & 0x01)
        return a;
    int b = min(l<len1? nums1[l]:INT32_MAX, mid-r<len2? nums2[mid-r]:INT32_MAX);
    return (a + b) / 2.0;
}

double findMedianSortedArraysMN(vector<int> &nums1, vector<int> &nums2)
{
    vector<int> merged;
    // ...
}

int main() {

    int a[10] = {0, 1, 2};
    int *b = a;
    cout << sizeof(a) << endl;    // 40
    cout << sizeof(b) << endl;    // 8

    return 0;
}

