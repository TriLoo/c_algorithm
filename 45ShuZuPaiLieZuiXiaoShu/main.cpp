/**
 * @author smh
 * @date 2018.08.18
 *
 * @brief 剑指offer第45题
 *   把数组排列成最小的数
 *
 *   思路：
 *      1. 定义一个新的比较函数，也就是说按照组合后数的大小进行排序！
 */
#include <iostream>
#include <algorithm>

using namespace std;

bool compareString(string s1, string s2)
{
    string comb1 = s1 + s2;
    string comb2 = s2 + s1;
    return less<string>()(comb1, comb2);
}

vector<string> getMinCombine(vector<string> values)
{
    sort(values.begin(), values.end(), compareString);
    return values;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N;
    cin >> N;
    vector<string> stringValues;
    int a = 0;
    for (int i = 0; i < N; ++i)
    {
        cin >> a;
        stringValues.push_back(to_string(a));
    }

    vector<string> results;
    results = getMinCombine(stringValues);
    for(auto ele : results)
        cout << stoi(ele);
    cout << endl;

    return 0;
}
