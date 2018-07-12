#include <iostream>
#include <vector>

using namespace std;

int getMax(const vector<int> & ups, const vector<int> & downs, int n)
{
    int currmax = 0;
    int currTotal = 0;
    for (int i = 0; i < n; ++i)
    {
        currTotal += (ups.at(i) - downs.at(i));
        if (currTotal > currmax)
            currmax = currTotal;
    }

    return currmax;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    int n;
    cin >> n;
    vector<int> ups(n, 0), downs(n, 0);
    for(int i = 0; i < n; ++i)
        cin >> downs.at(i) >> ups.at(i);

    cout << getMax(ups, downs, n) << endl;

    return 0;
}
