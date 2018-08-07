/**
 * \author smh
 * \date 2018.08.06
 *
 * \brief 剑指Offer第38题
 *
 * \brief 思路：
 *          1. 第一步求出所有可能出现在第一个位置的字符，即把第一个字符与后面所有的字符交换
 *          2. 第二步固定第一个字符，求后面所有字符的排列
 *          3. 可以用递归来做
 */
#include <iostream>

using namespace std;

//void PermutationCore(string &sin, int idx);
void PermutationCore(string &sin, const int& idx);

void Permutation(string sin)
{
    if (sin.length() <= 0)
        return;

    PermutationCore(sin, 0);
}

void PermutationCore(string &sin, const int& idx)
{
    int len = sin.length();
    if(idx == len)
        cout << sin << endl;
    else
        for (int i = idx; i < len; ++i)
        {
            // 交换
            char a = sin.at(idx);
            sin.at(idx) = sin.at(i);
            sin.at(i) = a;

            PermutationCore(sin, idx+1);

            // 更换回来
            a = sin.at(idx);
            sin.at(idx) = sin.at(i);
            sin.at(i) = a;
        }
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    string s;
    cin >> s;

    Permutation(s);

    return 0;
}
