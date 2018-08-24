/**
 * @author smh
 * @date 2018.08.24
 *
 * @brief 剑指offer第63题
 *   股票的最大利润
 *
 *   思路：
 *      1. 最大的利润就是最大的差值
 */
#include <iostream>
#include <vector>

using namespace std;

int getMaxProfit(vector<int> &values)
{
    if (values.size() <= 1)
        return 0;

    int minV = values.at(0);
    int currMax = values.at(1) - values.at(0);
    for (int i = 2; i < values.size(); ++i)
    {
        if (values.at(i-1) < minV)
            minV = values.at(i-1);

        int currDiff = values.at(i) - minV;
        if (currDiff > currMax)
            currMax = currDiff;
    }

    return currMax;
}

int main() {
    int N;
    cin >> N;
    vector<int> values(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> values.at(i);
    }

    if (values.size() == 0)
        return 0;

    cout << getMaxProfit(values) << endl;

    return 0;
}