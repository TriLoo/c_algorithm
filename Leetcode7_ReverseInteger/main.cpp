/**
 * @author smh
 * @date 2018.09.27
 *
 * @brief Leetcode 7 Easy
 *   Reverse Integer
 *
 *   思路： 通过栈的思想来完成，迭代pop出输入数据的最低位，以push的方式更新输出的数据的
 *         最需要注意的就是：避免溢出，包括极大溢出、两个方面
 *         以极大溢出为例：
 *              1. 若当前值curr > INT_MAX / 10，那么下一步就会溢出
 *              2. 若当前值curr == INT_MAX/10, 那么要加上的值大于7了那么就会溢出，(32位最大值的最低位为7,极小值溢出的情况为-8)
 */
#include <iostream>

using namespace std;

int reverse(int x)
{
    int t = 0;
    while(x != 0)
    {
        int pos = x % 10;
        x /= 10;
        // 两种溢出情况
        if(t > INT32_MAX/10 || (t == INT32_MAX/10 && pos > 7))
            return 0;
        if(t < INT32_MIN/10 || (t == INT32_MIN/10 && pos < -8))
            return 0;

        t = t * 10 + pos;
    }

    return t;
}

int main() {
    int i = -1;
    cout << i % 10 << endl;    // -1
    cout << INT32_MAX / 10 << endl;

    int a;
    cin >> a;
    cout << "a = " << a << endl;
    cout << reverse(a) << endl;

    return 0;
}