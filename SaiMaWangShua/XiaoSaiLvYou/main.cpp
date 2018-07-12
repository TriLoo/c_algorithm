#include <iostream>
#include <vector>

using namespace std;

int getCounts(const vector<int> & nodes, int N, int V)
{
    int total = 0;
    int dist = 0;
    for (int i = 0; i < V; ++i)
    {
        dist += nodes.at(i);
        if((i == 0) && (dist > N))
            return total;

        if (dist >= N)
        {
            ++total;
            dist = 0;
        }
    }

    return total;
}

int main() {
    int N, Villages;
    cin >> N >> Villages;
    vector<int> Nodes(Villages + 1, 0);

    for (int i = 0; i < Villages + 1; ++i)
        cin >> Nodes.at(i);

    cout << getCounts(Nodes, N, Villages + 1) << endl;

    return 0;
}
