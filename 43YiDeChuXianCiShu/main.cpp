/**
 * @author smh
 * @date 2018.08.22
 *
 * @brief 剑指offer第44题
 *   数字序列中某一位的数字
 *
 *   思路：
 *      1. 为方便处理，需要先将输入的int数值转换为字符串进行处理
 *      2. 整个过程分成三个部分：分成高位+零头两个部分，零头部分进行迭代
 *          A. 最高位中包含的1，又分成最高位大于1，最高位等于1两种情况下1的个数
 *          B. 考虑最高位情况下，剩下的低位中包含的1的个数
 */
#include <iostream>

using namespace std;

int getPowerTen(int n)
{
    int v = 1;
    for (int i = 0; i < n; ++i)
        v *= 10;

    return v;
}

int getNumOfOne(string a)
{
    int len = a.length();
    if (len == 0 || a == "0")
        return 0;

    if (a.at(0) < '0' || a.at(0) > '9')
        return 0;

    int first = a.at(0) - '0';
    int Num = 0;
    // 考虑最高位中包含1的个数
    if (first > 1)
        Num += getPowerTen(len - 1);
    else
        Num += stoi(a.substr(1, len-1)) + 1;   // 1 is the 100000...

    // 考虑最高位数字的低位中包含1的个数
    Num += first * (len-1) * getPowerTen(len-2);

    // 考虑最后一种情况：零头，迭代
    Num += getNumOfOne(a.substr(1));

    return Num;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int v = 0;
    cin >> v;
    cout << getNumOfOne(to_string(v)) << endl;

    return 0;
}
