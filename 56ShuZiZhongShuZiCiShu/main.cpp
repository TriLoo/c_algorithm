/**
 * @author smh
 * @date 2018.09.02
 *
 * @brief 剑指offer第56题
 *   数组中只出现一次的两个数字
 *
 *   思路：
 *     1. 对数组中所有的数字按位异或，可以得到这两个数字中特定为1的索引，然后根据这个索引将数组分成两部分，每个部分都有且只有一个出现一次的数字
 *     2. 根据然后对两个分组分别重新异或，得到那个只有一个位置为1的索引，然后根据这个索引得到这个只出现一次的数字
 */
#include <iostream>
#include <vector>

using namespace std;

int getBitIdx(int a);

bool isBit(int a, int idx)
{
    for (int i = 0; i < idx; ++i)
        a = a >> 1;

    return (a & 1);
}

void getUniqueTwo(vector<int> &a, int &b, int &c)
{
    int bitIdx = 0;
    int orNums = 0;
    for (auto & ele : a)
        orNums ^= ele;
    int firstIdx = getBitIdx(orNums);

    int lhs = 0, rhs = 0;
    for (auto ele : a)
    {
        if(isBit(ele, firstIdx))
            lhs ^= ele;
        else
            rhs ^= ele;
    }
}

int getBitIdx(int a)
{
    int idx = 0;
    while ((a & 0x01) == 0 && idx < 8 * sizeof(int))
    {
        a = a >> 1;
        ++idx;
    }

    return idx;
}

int main() {
    int N;
    cin >> N;
    vector<int> a(N, 0);
    for (int i = 0; i < N; ++i)
        cin >> a.at(i);
    int b, c;

    getUniqueTwo(a, b, c);
    cout << b << " " << c;

    return 0;
}
