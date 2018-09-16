#include <iostream>

using namespace std;

long getNsum(float n)
{
    long tempSum = 0;

    int a = n;
    float b = n - a;

    while(a)
    {
        tempSum += a % 10;
        a /= 10;
    }

    b *= 10;
    int c = b;
    while(c)
    {
        tempSum += c;
        b *= 10;
        c = static_cast<int>(b + 0.0001);
        b = b - c;
        c = c % 10;
    }

    return tempSum;
}

bool isHeXie(float n)
{
    long n_sum = getNsum(n);

    if(n == 0)
        return false;

    //if(n_sum % n)
    int a = n / n_sum;
    float b = n / n_sum;
    if(b-a)
        return false;
    else
        return true;
}

int main()
{
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        float n;
        cin >> n;
        if(isHeXie(n))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}
