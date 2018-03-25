/*
 * Author: smh
 * Description: 输入两个数：M,N，分别表示扇形的分区个数、以及颜色的个数。要求相邻
 *                  扇形不能有相同的颜色，那么一共可以有多少方案，用颜色填满所有的扇区
 *                  M >= 1, N >= 3
 */

#include <iostream>
#include <vector>
#include "memory"
#include "cmath"

using namespace std;

// M : 分区个数. N: 颜色的个数
// 递归
int countColor(const int M, const int N)
{
    if (M == 1)
        return N;
    if (M == 2)
        return N * (N - 1);

    if (M >= 3)
        return N * pow(N - 1, M - 1) - countColor(M - 1, N); // 被减去的情形为：最后的分区与相邻的最开始的分区具有相同的颜色
}

// 化简
// 上述递归其实是一个等比数列
int countColorFast(const int M, const int N)
{
    return pow(N - 1, M) + (N - 1) * pow(-1, M);
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    int colors, splits;
    cin >> splits >> colors;

    if (colors < 1 || splits < 3)
    {
        cerr << "Error Inputs." << endl;
        return EXIT_FAILURE;
    }

    //int Res = countColor(colors, splits);
    int Res = countColorFast(colors, splits);

    cout << "Total schemes: " << Res << endl;

    return 0;
}
