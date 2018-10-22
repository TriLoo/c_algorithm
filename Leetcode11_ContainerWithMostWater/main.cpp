/**
 * @author smh
 * @date 2018.10.21
 *
 * @brief Leetcode11 medium
 *   Container with most water
 *
 *   Note:
 *      Approach 1: Brute Force, O(n^2), O(1)
 *      Approach 2: Two Pointer Approach, see the 'Solution' panel for more details. O(n), O(1)
 *                  If we move the longer pointer, then the area won't increase, because it is limited by the length of shorter line !!
 *                  Meanwhile, we have to use a temporary variable to store current the maximum area.
 */
#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int>& height)
{
    int currMax = 0;

    int len = height.size();
    if(len <= 1)
        return 0;
    int i = 0, j = len - 1;
    int currArea = 0;
    while(i != j)
    {
        int a = height.at(i);
        int b = height.at(j);
        if(a < b)
        {
            currArea = (j - i) * a;
            ++i;
        }
        else
        {
            currArea = (j - i) * b;
            --j;
        }

        if(currArea > currMax)
            currMax = currArea;
    }

    return currMax;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int n;
    cin >> n;
    vector<int> caps(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> caps.at(i);

    cout << maxArea(caps) << endl;

    return 0;
}
