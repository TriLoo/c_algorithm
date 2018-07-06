#include <iostream>

using namespace std;

int getValue(const int n)
{
    if (n <= 2)
        return n;

    int i = 0;
    int step = 3;   // 注意，这里初始值为3，因为下降所发生的天数实际是从3开始递增的
    int k = 3;      // 初始值为3， 表明第k次发生下降

    while(k <= n)
    {
        ++i;
        k +=step;
        ++step;
    }

    return n - i * 2;   // * 2是因为，既需要减去前一次的上升，还需要减去这个位置的被占用
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    int n = 6;
    while(cin >> n)
        cout << getValue(n) << endl;

    return 0;
}
