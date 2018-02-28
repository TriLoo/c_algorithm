#include <iostream>
#include "vector"
#include "cmath"

using namespace std;

int Dynamic(int n)
{
    if (n <= 1)
        return 0;
    if (n == 2)
        return 1;
    if (n == 3)
        return 2;

    vector<int> maxLen(n + 1, 0);
    maxLen[0] = 0;
    maxLen[1] = 1;
    maxLen[2] = 2;
    maxLen[3] = 3;

    for (int i = 4; i <= n; ++i)
    {
        int maxCurr = 0;
        for (int j = 1; j <= i / 2; ++j)
        {
            int maxNext = maxLen[j] * maxLen[i - j];
            if (maxNext > maxCurr)
                maxCurr = maxNext;
        }
        maxLen[i] = maxCurr;
    }

    return maxLen[n];
}

int Greedy(int n)
{
    if (n <= 1)
        return 0;
    if (n == 2)
        return 1;
    if (n == 3)
        return 2;

    int times = n / 3;

    if (n - times * 3 == 1)
        times--;

    int timesOfTwo = (n - times * 3) / 2;

    return static_cast<int>(pow(3, times)) * static_cast<int>(pow(2, timesOfTwo));
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    cout << Dynamic(8) << endl;
    cout << Greedy(8) << endl;

    return 0;
}
