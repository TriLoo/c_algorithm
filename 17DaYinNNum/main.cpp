#include <iostream>
#include <vector>

using namespace std;

// 老老实实把一件事做好! 2018.07.29

void printNums(vector<char>& num)
{
    bool isBeginZero = true;
    for (const auto& ele : num)
    {
        if(ele != '0' && isBeginZero)
            isBeginZero = false;

        if (!isBeginZero)
        {
            cout << ele;
        }
    }
    if (!isBeginZero)
        cout << endl;
}

void printOneToN(vector<char>& nums, int starts)
{
    if (nums.size() == starts)
    {
        printNums(nums);
        return;
    }
    for (int i = 0; i <= 9; ++i)
    {
        nums.at(starts) = i + '0';
        printOneToN(nums, starts+1);
    }
}

void printOneToN(int N)
{
    if (N <= 0)        // N 大于 1
        return;

    vector<char> nums(N, '0');
    printOneToN(nums, 0);
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int N;
    cin >> N;

    printOneToN(N);

    return 0;
}
