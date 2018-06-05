#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

double doPower(double base, int exponent)
{
    if(exponent == 0)
        return 1;
    if(exponent == 1)
        return base;

    double result = 1.0;
    result = doPower(base, exponent >> 1);
    result *= result;
    if (exponent & 0x01)
        result *= base;

    return result;
}

double Power(double base, int exponent)
{
    if (equal_to<double>()(base, 0.0) && exponent == 0)
        throw runtime_error("Input Invalid.");

    int  Negative = exponent<0? -1 : 1;
    exponent *= Negative;
    double p = 1.0;

    if (exponent >= 1)
        p = doPower(base, exponent);
    else    // exponent = 0
        p = 1;

    p = (Negative == 1) ? p : 1.0 / p;

    return p;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    double base;
    int expValue;
    cin >> base >> expValue;

    double result = 0.0;
    try {
        result = Power(base, expValue);
    }
    catch (runtime_error err)
    {
        cout << err.what() << endl;
    }
    cout << "Result = " << result << endl;

    return 0;
}
