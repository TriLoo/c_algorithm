/**
 * @author smh
 * @date 2018.08.21
 *
 * @brief 剑指offer第47题
 *   礼物的最大价值
 *
 *   思路：
 *      1. 典型的动态规划问题，状态f(i, j)表示到达(i, j)处所能得到的最大价值，但这样会消耗m*n的存储空间。
 *      2. 进一步的优化是只需要一行额外的存储空间(n)，然后循环使用m次即可
 */
#include <iostream>

using namespace std;

int getMax(int a, int b)
{
    return a > b ? a : b;
}

// 每次只能向右或者向下移动一格
int getMaxValues(int **a, int m, int n)
{
    int *t = new int [n];

    t[0] = a[0][0];
    for (int i = 1; i < n; ++i)
        t[i] = t[i-1] + a[0][i];
    for (int i = 1; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (j == 0)
                t[j] += a[i][j];
            else
                t[j] = getMax(t[j-1] + a[i][j], t[j] + a[i][j]);
        }
    }

    int maxV = t[n-1];
    delete [] t;

    return maxV;
}

int main() {
    int n, m;
    cin >> n >> m;

    int **values = new int *[m];
    for (int i = 0; i < m; ++i)
        values[i] = new int [n];

    int c;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> c;
            values[i][j] = c;
        }
    }

    cout << getMaxValues(values, m, n) << endl;

    for (int i = 0; i < m; ++i)
        delete [] values[i];

    delete [] values;

    return 0;
}
