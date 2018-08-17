/**
 * @author smh
 * @date 2018.08.17
 *
 * @brief 剑指offer第40题
 *   最小的k个数
 *
 *   思路：
 *      1. 定义一个容量为k的有序容器，当每次新来一个数后就与这k个数的最大值进行比较，如果比它还小的话，就选择剔除最大的数，然后压入这个数
 *      2. 可以使用最大k堆实现,是指在树中，存在一个节点而且该节点有儿子节点，该节点的data域值都大于其儿子节点的data域值，并且是一个完全二叉
 *         树。
 *      3. C++中的set和multiset都是基于红黑树实现的,
 */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

using intSet = std::multiset<int, greater<int>>;
//using intSetIter = std::multiset<int, greater<int>>::iterator;

void getKMinimum(vector<int>& values, intSet & kSet,int k)
{
    if (values.size() == 0)
        return ;

    if (k > values.size() || k < 0)
        return;

    auto setBegin = kSet.begin();

    for (int i = 0; i < values.size(); ++i)
    {
        if (kSet.size() < k)
            kSet.insert(values[i]);
        else
        {
            auto setBegin = kSet.begin();
            if (values.at(i) < *setBegin)
            {
                kSet.erase(setBegin);
                kSet.insert(values[i]);
            }
        }
    }
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> values(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> values.at(i);
    }
    intSet kMinums;
    getKMinimum(values, kMinums, K);

    for (auto ele : kMinums)
        cout << ele << endl;

    return 0;
}
