#include <iostream>
#include <vector>

using namespace std;

// 递归的方法
int getMethods(const int m)
{
    if(m == 1)
        return 1;
    if(m == 2)
        return 1;

    return getMethods(m-1) + getMethods(m-2);
}

// 从下往上的方法
int getMethodsB2U(const int m) {
    if (m == 1)
        return 1;
    if (m == 2)
        return 1;

    int prev=1, next=1;
    int curr=0;
    for (int i = 3; i <= m; ++i)
    {
        curr = prev + next;
        prev = next;
        next = curr;
    }

    return curr;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    int t = 0;
    cin >> t;
    int step = 0;

    for(int i = 0; i < t; ++i)
    {
        cin >> step ;
        cout << getMethodsB2U(step) << endl;
    }

    return 0;
}
