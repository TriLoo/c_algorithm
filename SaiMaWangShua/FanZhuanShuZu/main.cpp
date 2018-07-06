#include <iostream>
#include <memory>

using namespace std;

// 默认的输入的数组是元素均不相同
bool testInvertable(int *a, const int n)
{
    if(n == 1)
        return true;

    int i = 1;   // 下一个元素
    int j = 0;   // 上一个元素

    int tempA = a[i], tempB = a[j];

    while(a[i] > a[j])
    {
        ++i;
        ++j;

        if (i >= n)
            return false;
    }

    tempA = a[j];   // 此时没有返回，说明遇到了降序的数组了, 此时记录降序数组的最大值

    while(a[i] < a[j])
    {
        ++i;
        ++j;
        if(i >= n)
            return true;
    }

    tempB = a[i];   // 此时同样没有返回，说明重新遇到了升序的数组了，此时记录升序数组里面的最小值

    while(i < n)
        if(a[i++] < a[j++])
            return false;

    return tempA < tempB;
}

int main(int argc, char ** argv) {
    //std::cout << "Hello, World!" << std::endl;

    int n = 1;
    cin >> n;    // The number of elements

    int *a = new int [n];

    for(int i = 0; i < n; ++i)
        cin >> a[i];

    if (testInvertable(a, n))
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    delete [] a;

    return 0;
}
