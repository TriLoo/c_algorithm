#include <iostream>

using namespace std;

long long Fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

long long FibonacciFast(int n)
{
    if (n <= 1)
        return n;

    int fNminsOne = 1;
    int fNminsTwo = 0;
    int fCurr = 0;

    for (int i = 2; i <= n; ++i)
    {
        fCurr = fNminsOne + fNminsTwo;

        fNminsTwo = fNminsOne;
        fNminsOne = fCurr;
    }

    return fCurr;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    cout << "Result = " << Fibonacci(7) << endl;
    cout << "Result Fast = " << FibonacciFast(7) << endl;

    return 0;
}
