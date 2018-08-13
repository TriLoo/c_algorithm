/**
 * \author smh
 * \date 2018.08.11
 *
 * \brief 背包问题
 *   华为2019校招笔试。
 *
 * 基于动态规划来做。
 */
#include <iostream>
#include <vector>

using namespace std;

int maxCompare(int a, int b)
{
    return a > b ? a : b;
}

/**
 * \brief 实现函数
 * 基于动态规划求解0-1背包问题
 *
 * 状态变量：f[i][j] 表示在前i件物品中选择若干件放在承重为j的背包中，可以取得的最大价值，假设第i件物品的重量为P_j，那么状态转移函数为：
 *              f[i, j] = Max{f[i-1, j-W] + p_i(j >= W_i), f[i-1, j]}
 * 解释： 在max{}中的第一项是f[i-1][j-W],也就是说在前i-1个物品中，含有j-W的重量的物品的最大价值 + 加上本次物品的重量以及价值
 *       第二项，为本此物品不是最优的选项时，等价于在前i-1个物品中，承重限制为j的情况下的最大价值
 *
 * @param values
 * @param weights
 * @return
 */
int getMaxValue(vector<int> &values, vector<int> &weights, int C)
{
    int len = values.size();
    int ** maps = new int * [len+1];
    for (int i = 0; i < len + 1; ++i)
        maps[i] = new int [C+1];

    // i: 前i个物品，j:重量限制
    for (int i = 0; i < C+1; ++i)
        maps[0][i] = 0;
    for (int i = 1; i < len+1; ++i)
        maps[i][0] = 0;

    for (int i = 1; i < len+1; ++i)
    {
        int v = values.at(i-1);
        int w = weights.at(i-1);
        for (int j = 1; j < C+1; ++j)
        {
            if (j < w)
                maps[i][j] = maps[i-1][j];
            else
                maps[i][j] = maxCompare(maps[i-1][j-w] + v, maps[i-1][j]);
        }
    }

    cout << "success." << endl;

    int maxValue = maps[len][C];

    for (int i = 0; i < len+1; ++i)
        delete [] maps[i];

    delete [] maps;

    return maxValue;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N, M;
    cin >> N >> M;
    vector<int> Values(N, 0);
    vector<int> Weights(N, 0);

    for (int i = 0; i < N; ++i)
        cin >> Values.at(i);
    for (int i = 0; i < N; ++i)
        cin >> Weights.at(i);

    cout << getMaxValue(Values, Weights, M) << endl;

    return 0;
}
