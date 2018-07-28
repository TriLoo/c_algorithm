#include <iostream>
#include <cmath>
//#include <>
//#include <algorithm>

using namespace std;

bool equal(double a, double b)
{
    return abs(a - b) < 0.0000000001;
}

double getExponentUnsigned(double base, int exp_num)
{
    if (exp_num == 0)
        return 1;
    if (exp_num == 1)
        return base;

    double currVal = 0.0;

    currVal = getExponentUnsigned(base, exp_num >> 1);
    currVal *= currVal;

    if (exp_num & 0x01)    // 奇数
        currVal *= base;

    return currVal;
}

double Power(double base, int exponent)
{
    if(equal(base, 0.0) && exponent < 0)
        exit(1);

    int exp_in = exponent;
    double result = 0;
    if(exponent < 0)
        exp_in = -1 * exponent;

    result = getExponentUnsigned(base, exp_in);

    if (exponent < 0)
        result = 1.0 / result;

    return result;
}


int main() {
    //std::cout << "Hello, World!" << std::endl;
    double base;
    int exponent;

    cin >> base >> exponent;

    cout << Power(base, exponent) << endl;

    return 0;
}
