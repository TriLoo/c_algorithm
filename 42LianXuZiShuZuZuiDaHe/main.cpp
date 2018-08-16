/**
 * \author smh
 * \date 2018.08.14
 *
 * \brief 剑指offer第42题
 * 连续子数组的最大和
 *
 * \brief 思路：
 *          1. 用两个变量，一个保存到达当前位置已有的最大的值，另一个保存当前位置可能实现的最大的值，如果当前位置的和是负值就丢弃掉
 *          2. 动态规划，与上面的思路是一样的，状态定义为当前位置可能的最大的加和，然后最后找出各个位置中最大的那个加和就是结果
 */
#include <iostream>
#include <vector>

using namespace std;

int getMaxSum(vector<int>& values)
{
    int currSum=values.at(0), maxSum = values.at(0);
    int len = values.size();
    for (int i = 1; i < len; ++i)
    {
        if (currSum <= 0)
            currSum = values.at(i);
        else
            currSum += values.at(i);

        if(currSum > maxSum)
            maxSum = currSum;
    }

    return maxSum;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N;
    cin >> N;
    vector<int> values(N, 0);
    for (int i = 0; i < N; ++i)
        cin >> values.at(i);

    if (values.size() == 0)
        return 0;

    cout << getMaxSum(values) << endl;

    return 0;
}
