/**
 * @author smh
 * @date 2018.09.11
 *
 * @brief 剑指offer第41题
 *   数据流中的中位数
 *
 *   思路：
 *      1. 根据中位数的定义，就是中间一个数或两个数的平均值
 *      2. 统一的思路是：维持一个数据结构，然后得到中位数，该结构可以是有序也可以是无序
 *      3. 这里采用两个堆来实现: 偶数索引的数放在左堆，奇数索引的数放在右堆。需要保证左堆小于右堆，所以每次插入时需要保证堆的根节点的有序性
 */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// TODO: fixbugs: use multiset instead
using setIter = set<int>::iterator;

// 另一种中做法
template <typename T>
class DynamicArray
{
public:
    void Insert(T a)
    {
        if((minHeap.size() + maxHeap.size()) & 0x01 == 0)   // 为偶数，默认放在最小堆中
        {
            if(maxHeap.size() > 0 && a < maxHeap[0])
            {
                maxHeap.push_back(a);
                push_heap(maxHeap.begin(), maxHeap.end(), less<T>());

                a = maxHeap[0];

                pop_heap(maxHeap.begin(), maxHeap.end(), less<T>());
                maxHeap.pop_back();
            }

            minHeap.push_back(a);
            push_heap(minHeap.begin(), minHeap.end(), greater<T>());
        }
        else   // 为奇数，默认放在最大堆中
        {
            // 判断是否大于最小堆的根节点
            if(minHeap.size() > 0 && minHeap[0] < a)
            {
                minHeap.push_back(a);
                push_heap(minHeap.begin(), minHeap.end(), greater<T>());

                a = minHeap[0];

                pop_heap(minHeap.begin(), minHeap.end(), greater<T>());
                minHeap.pop_back();
            }

            maxHeap.push_back(a);
            push_heap(maxHeap.begin(), maxHeap.end(), less<T>());
        }
    }

    T getMidNum()
    {
        int sizeT = minHeap.size() + maxHeap.size();
        if(sizeT == 0)
            return static_cast<T>(0);

        T median = 0;
        if((sizeT & 0x01) == 0)
            median = (minHeap[0] + maxHeap[0]) >> 1;
        else
            median = minHeap[0];

        return median;
    }

private:
    vector<T> minHeap;
    vector<T> maxHeap;
};


int main() {
    int n;
    set<int, greater<int>> leftEven;   // 最大堆
    set<int> rightOdd;   // 最小堆, 升序
    int midNum = 0;
    int i = 0;
    while(cin >> n)
    {
        if(i++ & 0x01)   // 奇数
            rightOdd.insert(n);
        else
            leftEven.insert(n);

        // 处理堆顶
        auto lbeg = leftEven.begin();
        auto rbeg = rightOdd.begin();
        if(*lbeg > *rbeg)    // 左边的堆顶大于右边的堆顶
        {
            int a = *lbeg;
            leftEven.erase(lbeg);
            leftEven.insert(*rbeg);
            rightOdd.erase(*rbeg);
            rightOdd.insert(a);
        }
    }

    if(i & 0x01)
        midNum = *(leftEven.begin());
    else
        midNum = (*(leftEven.begin()) + *(rightOdd.begin())) >> 1;

    cout << midNum << endl;

    return 0;
}
