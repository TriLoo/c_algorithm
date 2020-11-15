/**
 * \file main.cpp
 * \author smh
 * \date 2020.11.15
 * \brief
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

using namespace std;

class MinHeap {
    public:
        MinHeap(){}
};

class Solution {
    public:
        // solution - 1: minimum heap based on vector
        int findKthLargest(vector<int> &nums, int k)
        {
            vector<int> tmp_heap(k, 0);
            for (int i = 0; i < k; ++i)
                tmp_heap[i] = nums[i];
            make_heap(tmp_heap.begin(), tmp_heap.end(), greater<int>());
            for (int i = k; i < nums.size(); ++i)
            {
                int val = nums[i];
                if (val > tmp_heap[0])
                {
                    swap(tmp_heap[0], tmp_heap[k-1]);
                    tmp_heap.pop_back();
                    tmp_heap.push_back(val);
                    make_heap(tmp_heap.begin(), tmp_heap.end(), greater<int>());
                }
            }
            return tmp_heap[0];
        }
        // solution - 2: minimum heap based on priority queue
        int  findKthLargest_v2(vector<int>& nums, int k)
        {
            int n = nums.size();
            if (n == 0 || k > n)
                return 0;
            priority_queue<int, vector<int>, greater<int> > q;
            for(int i = 0; i < n; ++i)
            {
                q.push(nums[i]);
                if (q.size() > k)
                    q.pop();
            }

            return q.top();
        }
};

int main()
{
    return 0;
}

