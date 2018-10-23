/**
 * @author smh
 * @date 2018.10.23
 *
 * @brief Leetcode 11 Medium
 *   Integer to Roman
 *
 *   Notes:
 */
#include <iostream>
#include <map>

using namespace std;

string intToRoman(int num)
{
    string Ms[] = {"", "M", "MM", "MMM"};
    string Cs[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string Xs[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string Is[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    return Ms[num/1000] + Cs[(num % 1000)/100] + Xs[(num % 100) / 10] + Is[num%10];
}

/*
string intToRoman(int num)
{
    string ret;
    map<int, char> symVal;

    symVal.insert(pair<int, char>(1,     'I'));
    symVal.insert(pair<int, char>(5,     'V'));
    symVal.insert(pair<int, char>(10,    'X'));
    symVal.insert(pair<int, char>(50,    'L'));
    symVal.insert(pair<int, char>(100,   'C'));
    symVal.insert(pair<int, char>(500,   'D'));
    symVal.insert(pair<int, char>(1000,  'M'));

    int n = 0;
    int  perNum[4] = {-1, -1, -1, -1};

    // 计算输入整数的位数
    while(num)
    {
        perNum[n] = num % 10;
        ++n;
        num /= 10;
    }

    if(perNum[3] != -1)
    {
        for (int i = 0; i < perNum[3]; ++i)
            ret.push_back('M');
    }

    if(perNum[2] != -1)
    {
        switch (perNum[2])
        {
            case 9:
                ret.push_back('C');
                ret.push_back('M');
                break;
            case 4:
                ret.push_back('C');
                ret.push_back('D');
                break;
            default:
                ret.push_back(symVal[]);
        }
    }


    return ret;
}
*/

int main() {
    int a;
    cin >> a;   // input is within the range from 1 to 3999.

    cout << intToRoman(a) << endl;

    return 0;
}
