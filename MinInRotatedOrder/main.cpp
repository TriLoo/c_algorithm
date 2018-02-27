#include <iostream>
#include "vector"
#include "iterator"
#include "algorithm"
#include "stdexcept"

using namespace std;

int MinInOrder(const vector<int> &data)
{
    if (data.empty())
        throw runtime_error("No input data.");

    auto beg = data.cbegin();
    auto tail = data.cend();
    auto mid = ((tail - beg) >> 1) + beg;   // correct

    int value = *beg;

    // Cannot return the minimum value
    if (*mid == *beg && *beg == *tail)
        throw runtime_error("Not sorted data.");

    // Not a  rotated array
    if (greater<int>()(*tail, *beg))
        return value;

    // Rotated array
    while(tail > beg + 1)
    {
        if (greater<int>()(*mid, *beg))
            beg = mid;
        else
            tail = mid;

        mid = ((tail - beg) >> 1) + beg;
    }

    return *tail;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    vector<int> data{3, 4, 5, 0, 2};

    int min = MinInOrder(data);
    cout << "Min = " << min << endl;

    // Test less algorithm
    //if (less<int>()(1, 2))
        //cout << "True." << endl;

    return 0;
}
