#include<iostream>
#include<vector>

using namespace std;

class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int currMaxCost = cost.at(0);
        if(cost.size() <= 1)
            return 0;
        if (cost.size() == 2)
            return min(cost.at(0), cost.at(1));

        vector<int> currCost(cost.size(), 0);
        currCost.at(0) = cost.at(0);   // only one stair
        currCost.at(1) = cost.at(1);    // only two stair

        for (int i = 2; i < cost.size(); ++i)
        {
            currCost.at(i) = cost.at(i) + min(currCost.at(i - 1), currCost.at(i - 2));
        }

        return min(currCost.back(), currCost.at(cost.size() - 2));
    }
};


int main()
{
    vector<int> cost = {10, 15, 20};
    Solution sl;

    cout << sl.minCostClimbingStairs(cost) << endl;

    return 0;
}
