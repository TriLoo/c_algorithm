#include <iostream>
#include <cassert>

/**
 * Dynamic Programming: exercise 1
 *
 * Author: smh
 * Data  : 2018.07.07
 */

using namespace std;

// n: 人数
// m: 传了m次
int getMethods(const int n, const int m)
{
    assert(n >= 3 && m >= 1);
    // 定义二维矩阵dp: 横：传递的次数；列：人员编号
    int nums=0;
    // create 2d array
    // dp[i][j]表示第i次传递到j个人的方式数,所以最后的结果就是：dp[m-1][0]
    int ** dp = new int *[m];
    for (int i = 0; i < m; ++i)
        dp[i] = new int [n];

    // 第一次传递
    // 假设起始点是0，那么从0到0的方式是1， 从零到n-1的方式数也是1
    for (int i = 0; i < n; ++i)
    {
        if (i == 1 || i == n-1)
            dp[0][i] = 1;
        else
            dp[0][i] = 0;
    }
    // 后面的传递
    for (int i = 1; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (j == 0)
                dp[i][j] = dp[i-1][j+1] + dp[i-1][n-1];
            else if (j == n-1)
                dp[i][j] = dp[i-1][0] + dp[i-1][j-1];
            else
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1];
        }
    }


    nums = dp[m-1][0];

    // delete 2d array
    for (int j = 0; j < n; ++j)
        delete [] dp[j];
    delete [] dp;

    return nums;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    int n, m;
    cin >> n >> m;

    cout << getMethods(n, m) << endl;

    return 0;
}
