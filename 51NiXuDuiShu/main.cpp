/**
 * @author smh
 * @date 2018.08.17
 *
 * @brief 剑指offer第51题
 *   数组中的逆序对数
 *
 *   思路：
 *      1. 基于归并排序计算逆序对数, 最大复杂度为NlgN
 *      2. 另一种方法是暴力求解，对于每一个数字都将其与后面的数字进行比较，计算出逆序对数，复杂度是N^2
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void merge(vector<int> a, int lo, int mid, int hi, int &sumV, vector<int> &aux)
{
    int i = lo, j = mid+1;
    for (int k = lo; k <= hi; ++k)
        aux.at(k) = a.at(k);

    for (int k = lo; k <= hi; ++k)
    {
        if(i > mid)
            a.at(k) = aux[j++];
        else if(j > hi)
            a.at(k) = aux[i++];
        else if(greater<int>()(aux[i], aux[j]))
        {
            sumV += j - mid;
            a.at(k) = aux[j++];
        }
        else
            a.at(k) = aux[i++];
    }
}

// 自上而下的递归实现
void mergeSort(vector<int> &a, int lo, int hi, int &sumV, vector<int>& aux)
{
    if(hi <= lo)
        return ;
    int mid = lo + (hi - lo) / 2;
    mergeSort(a, lo, mid, sumV, aux);
    mergeSort(a, mid+1, hi, sumV, aux);
    merge(a, lo, mid, hi, sumV, aux);
}

int getNumOfInversePair(vector<int>& a, vector<int> &aux)
{
    if (a.size() <= 1)
        return 0;

    int Sum = 0;
    mergeSort(a, 0, a.size()-1, Sum, aux);

    return Sum;
}

// 自下而上的方式
int calculate(vector<int> &a, vector<int> &aux)
{
    if (a.size() <= 1)
        return 0;

    int N = a.size();
    int Sum = 0;
    for (int sz = 1; sz < N; sz *= 2)      // 步长
    {
        for (int i = 0; i < N-sz; i += 2*sz)
        {
            int hi = i + 2 * sz - 1;
            hi = hi > N-1 ? N-1 : hi;
            merge(a, i, i+sz-1, hi, Sum, aux);
        }
    }

    return Sum;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N;
    cin >> N;
    vector<int> values(N, 0);
    vector<int> aux(N, 0);
    for (int i = 0; i < N; ++i)
        cin >> values.at(i);

    for (int i = 0; i < N; ++i)
        aux.at(i) = values[i];

    //cout << getNumOfInversePair(values, aux) << endl;
    cout << calculate(values, aux) << endl;

    return 0;
}
