#include <iostream>

using namespace std;

int numberA(int n)
{
    int flag = 1;
    int count = 0;
    while(flag)
    {
        if(flag & n)
            count++;
        flag = flag << 1;
    }

    return count;
}

int numberB(int n)
{
    int cnt = 0;
    while(n)
    {
        ++cnt;
        n = (n - 1) & n;
    }

    return cnt;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    cout << "Number of 1 in 'C': " << numberA(12) << endl;
    cout << "Number of 1 in 'C': " << numberB(12) << endl;

    return 0;
}
