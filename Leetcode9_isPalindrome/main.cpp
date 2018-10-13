/**
 * @author smh
 * @date 2018.10.12
 *
 * @brief Leetcode 9
 *   Palindrome Number: Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.
 *
 *   Note: convert a negative number to string, the negative symbol (-1) is also transferred into result string.
 *
 *   Here, we don't solve it with converting the integer to a string.
 */
#include <iostream>

using namespace std;

bool isPalindrome(int x)
{
    if(x < 0)
        return false;

    if((x % 10 == 0) && (x != 0))
        return false;

    int revertedNumber = 0;
    // 终止的时候，revertedNumber会比新的x多一位, 或者两者是相等的
    while(x > revertedNumber)
    {
        revertedNumber = revertedNumber * 10 + x % 10;
        x /= 10;
    }

    // 对应的两个条件分别是：位数为偶数时，位数为奇数时的两种情况。
    return (x == revertedNumber) || (x == revertedNumber / 10);
}

int main() {
    int a = -1;
    string s = to_string(a);
    cin >> a;

    if(isPalindrome(a))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}