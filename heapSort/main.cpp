/**
 * @author smh
 * @date 2018.08.18
 *
 * @brief 堆排序
 *  堆排序
 *
 *  流程：
 *  性能： NlgN
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 首先定义最大堆
template <typename T>
class maxHeap
{
public:
    maxHeap(T a): values_(a)
    {
    }

    void insert(T v);

    void sink(int i);
    T deleteMax();
    void swim(int i);
    vector<T>  heapSortCore();

    int getEleNums();

private:
    bool compareT(int i, int j);
    void exch(int i, int j);
    vector<T> values_;
};

template <typename T>
T maxHeap<T>::deleteMax()
{
    T a = values_.at(1);
    int N = getEleNums();
    exch(1, N);
    auto iter = --values_.end();
    values_.erase(iter);

    return a;
}

template <typename T>
void maxHeap<T>::exch(int i, int j)
{
    T a = values_.at(i);
    values_.at(i) = values_.at(j);
    values_.at(j) = a;
}

template <typename T>
bool maxHeap<T>::compareT(int i, int j)
{
    return less<T>()(values_.at(i), values_.at(j));
}

template <typename T>
int maxHeap<T>::getEleNums()
{
    return values_.size() - 1;
}

template <typename T>
void maxHeap<T>::insert(T v)
{
    values_.push_back(v);
    int N = getEleNums();
    sink(N);
}

template <typename T>
void maxHeap<T>::sink(int i)
{
    int N = getEleNums();
    while (2 * i <= N)
    {
        int j = 2 * i;
        if (j < N && compareT(j, j+1))
            ++j;
        if (!compareT(i, j))
            break;
        exch(i, j);
        i = j;
    }
}

template <typename T>
void maxHeap<T>::swim(int i)
{
    while (i > 1 && compareT(i/2, i))
    {
        exch(i/2, i);
        i = i/2;
    }
}

template <typename T>
vector<T> maxHeap<T>::heapSortCore() \
{
    int N = getEleNums();
    vector<T> sortedValues;
    for (int i = 0; i <= N; ++i)
        sortedValues.push_back(deleteMax());

    return sortedValues;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    // Under Tested

    return 0;
}
