#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// 对输入的lands排序，然后返回最大的距离除以2
double getDist(const vector<double> &lands, const double dist)
{
    vector<double> tempLands(lands.begin(), lands.end());
    // 对输入的vector进行排序
    sort(tempLands.begin(), tempLands.end());

    double currMax = 0.0;

    for (int i = 1; i < tempLands.size(); ++i)   // vector::size() returns the elements in the vector
        if(currMax < (tempLands.at(i) - tempLands.at(i-1)))
            currMax = tempLands.at(i) - tempLands.at(i-1);

    double firstDist = tempLands.front();        // front() return a reference to the last element
    if(firstDist > 0.00001)   // 认为在起始位置没有路灯
        if(firstDist * 2 > currMax)
            currMax = firstDist * 2;

    double lastDist = dist - tempLands.back();   // back() return a reference to the last element in the vector
    if (currMax < lastDist * 2)    // 此时在终点没有路灯
        currMax = lastDist * 2;

    return currMax / 2.0;
}

int main(int argc, char ** argv)
{
    int n;
    double l;
    cin >> n >> l;

    vector<double> ai(n, 0.0);

    double a_th = 0.0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a_th;
        ai.at(i) = a_th;
    }

    double d = getDist(ai, l);

    cout << fixed << setprecision(2) << d << endl;

    return 0;
}
