#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compareInt(int a, int b)
{
    return a > b;
}

int getMin(vector<int>& a, vector<pair<int, int>>& steps)
{
    vector<int> b = a;
    stable_sort(b.begin(), b.end(), compareInt);
    int balanceValue = b.front() - b.back();

    if (balanceValue == 0)
        return balanceValue;

    int maxV, minV;
    maxV = a.front();
    minV = a.front();

    int maxIdx = 0, minIdx = 0;
    for (int i = 1; i < a.size(); ++i)
    {
        if (maxV < a.at(i))
        {
            maxV = a.at(i);
            maxIdx = i;
        }
        if (minV > a.at(i))
        {
            minV = a.at(i);
            minIdx = i;
        }
    }

    balanceValue = maxV - minV;

    ++a.at(minIdx);
    --a.at(maxIdx);

    steps.push_back(make_pair(maxIdx+1, minIdx+1));

    return balanceValue;
}

int main() {
    int n, k;
    while(cin >> n >> k)
    {
        vector<int> heights(n, 0);
        for (int i = 0; i < n; ++i) {
            cin >> heights.at(i);
        }

        vector<pair<int, int>> steps;

        int minValue = 0, ops = 1;
        minValue = getMin(heights, steps);
        for (; ops <= k && minValue != 0; ++ops)
        {
            minValue = getMin(heights, steps);
        }

        if(ops == k+1)
            cout << minValue << " " << --ops << endl;
        else
            cout << minValue << " " << ops << endl;
        for (auto & ele : steps)
            cout << ele.first << " " << ele.second << endl;
    }

    return 0;
}
