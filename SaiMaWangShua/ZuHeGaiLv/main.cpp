#include <iostream>
#include <iomanip>

using namespace std;

double getProb(const int x, const int a, const int b, const int n)
{
    if(a * n > x || b * n < x)
        return 0;

    double count  = 0.0;
    const int inter = b - a + 1;
    // 每一个元素表示第i次获得该数的概率
    double **dp = new double * [n+1];
    for (int i = 0; i <= n; ++i)
        dp[i] = new double [x+1];

    double init_prob = 1.0 / inter;
    for (int i = a; i <= b; ++i)
        dp[1][i] = init_prob;

    for(int i = 2; i <= n; ++i)
    {
        for (int j = i*a; j <= x; ++j)
        {
            dp[i][j] = 0;
            for (int k = a; k <= b; ++k)
                dp[i][j] += dp[1][k] * dp[i-1][j-k];   // 概率相乘
        }
    }

    count = dp[n][x];

    // deconstruct
    for (int i = 0; i <= n; ++i)
        delete [] dp[i];
    delete [] dp;

    return count;
}

int main(int argc, char **argv) {
    //std::cout << "Hello, World!" << std::endl;

    int n, a, b, x;
    cin >> n >> a >> b >> x;

    double prob;
    prob = getProb(x, a, b, n);

    // 输出固定小数位数的方法
    // 先用fixed设置为定点数，然后后面设置的精度其实就是小数点后面的位宽了。
    //cout << fixed << setprecision(2) << pi << endl;
    cout << fixed << setprecision(4) << prob << endl;   // 即具有4位小数

    return 0;
}

