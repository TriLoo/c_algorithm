/**
 * \author smh
 *
 * \date 2018.08.01
 *
 * \brief 剑指Offer第21题：让奇数位于偶数之前
 *
 * \brief 思路：
 *          1. 类似于快速排序的方式，两个指针分别从前、后遍历整个数组
 *          2. 需要考虑可扩展性
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 判断是否为奇数，如果是奇数，返回ture
 *
 * @param a
 * @return bool
 */
template <typename T>
bool compareEvenOdd(T a)
{
    if (a & 0x01)
        return 1;
    else
        return 0;
}

template <typename T>
void exch(T &a, T &b)
{
    T c;
    c = a;
    a = b;
    b = c;
}

template <typename T>
void resortVector(vector<T> &a, bool (*fun)(T))
{
    int len = a.size() - 1;

    if (len <= 1)
        return;

    int i = 0, j = len;
    while (i < j)
    {
        while (i <= len && fun(a.at(i++)));
        while (j <= len && !fun(a.at(j--)));

        if (i < j)
        {
            T c = a.at(i-1);
            a.at(i-1) = a.at(j+1);
            a.at(j+1) = c;
        }
    }
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N;   // 元素个数
    cin >> N;
    vector<int> ain(N, 0);
    for (int i = 0; i < N; ++i)
        cin >> ain.at(i);

    cout << "Before Sorted." << endl;
    for (auto ele : ain)
        cout << ele <<endl;

    resortVector(ain, compareEvenOdd);

    cout << "After Sorted." << endl;
    for (auto ele : ain)
        cout << ele <<endl;

    return 0;
}

