/**
 * @author smh
 * @date 2018.09.29
 *
 * @brief Leetcode 8
 *   String to Integer (atoi)
 *
 *   Implement *atoi* which converts a string to an integer
 *   思路：
 *      1.
 */
#include <iostream>

using namespace std;

int myAtoi(string str)
{
    // case 0: str is null
    if(str.length() == 0)
        return 0;

    int ret = 0;
    bool isPos = true;
    bool isFirstChar = true;
    for(auto &ele : str)
    {
        // case 1: ele == backspace
        if(isFirstChar && (ele == ' '))
            continue;

        // case 2: if first no backspace 'ele' is not a number or +-, return 0
        if(isFirstChar)
        {
            isFirstChar = false;

            if((ele != '+') && (ele != '-') && (ele > '9' || ele < '0'))
                return 0;

            if(ele == '-')
                isPos = false;
            else if(ele == '+')
                continue;
            else
                ret = ele - '0';

            continue;
        }

        if(ele == ' ')
            break;

        // case 3: normal case
        // Judge the out of the range case
        if(ret > INT32_MAX/10 || (ret == INT32_MAX && (ele - '0') > 7))
        {
            if(isPos)
                return INT32_MAX;
            else
                return INT32_MIN;
        }

        ret = ret * 10 + (ele - '0');
    }

    return ret;
}

int main() {
    std::cout << "Hello, World!" << std::endl;


    return 0;
}
