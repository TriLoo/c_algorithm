/**
 * @author smh
 * @date 2018.08.23
 *
 * @brief 剑指offer第61题
 *   扑克牌中的顺子
 *
 *   从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。2~10为数字本身，A为1，J为11，Q为12， K为13
 *   而大小王可以看成任意数字。
 *   思路：
 *      1. 把大小王用0表示
 *      2. 首先对5个元素的数组进行排序；然后统计其中0的个数；然后统计数组中相邻数字之间的空缺总数。
 *      3. 如果空缺的总数小于或者等于0的个数，那么这个数组就是连续的；反之就是不连续的。另外，如果有相同的两个数，那么就不可能是顺子。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isSequence(vector<int> values)
{
    sort(values.begin(), values.end());       // Increment order default
    int numZero = 0;
    int i = 0;
    for (; values.at(i) == 0 ; ++i)
        ++numZero;

    int numGap = 0;
    for(int j = i; j < 4; ++j)
    {
        if (values.at(j+1) == values.at(j))
            return false;
        numGap += values.at(j+1) - values.at(j);
    }

    if (numZero >= numGap)
        return true;
    else
        return false;
}


int main() {
    vector<int> values(5, 0);
    for (int i = 0; i < 5; ++i)
        cin >> values.at(i);

    if (isSequence(values))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
