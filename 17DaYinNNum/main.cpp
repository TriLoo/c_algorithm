#include <iostream>
#include <vector>

using namespace std;

ostream&  print_char_vector(const vector<char> & nums)
{
    bool isBegion0 = true;
    size_t N = nums.size();

    for (auto ele : nums)
    {
        if ((ele != '0') && isBegion0)
            isBegion0 = false;

        if (!isBegion0)
            cout << ele;
    }
    if (isBegion0)      // 输出最开始的0
        cout << '0';

    return cout;
}

void printOneToN_Curr(const int length, vector<char>& a)
{
    if (length )
}

// N: 十进制的位数
void printOneToN(size_t N)
{
    // 输入检查
    if (N <= 0)
        return;

    for (int i = 0; i < N; ++i)
    {
        vector<char> nums(i+1, '0');
        for (int j = 0; j < 9; ++j) {
            nums.at(i) = static_cast<char>(j + '0');
            printOneToN_Curr(j+1, nums);
        }
    }
}

int main() {
    size_t N;
    cin >> N;

    printOneToN(N);
    cout << '1' + 1 << endl;
    cout << '1' << endl;
    //cout << static_cast<char>(1) << endl;
    //cout << static_cast<char>(48) << endl;

    return 0;
}
