#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //std::cout << "Hello, World!" << std::endl;

    int n, m;
    cin >> n >> m;

    vector<int> weights(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> weights.at(i);

    int new_m = m * 3;
    vector<int> ops(new_m, 0);
    for (int j = 0; j < new_m; j += 3)
        cin >> ops.at(j) >> ops.at(j+1) >> ops.at(j+2);

    for (int k = 0; k < new_m; k += 3)
    {
        if(ops.at(k) == 1)
            continue;
        else if(ops.at(k) == 2)
        {
            int totalsum = 0;
            for (int i = ops.at(k+1) - 1; i <= ops.at(k+2) - 1; ++i)
                totalsum += weights.at(i);

            cout << totalsum << endl;
        }
        else if(ops.at(k) == 3)
        {
            int max = weights.at(ops.at(k+1)-1);
            int currval = 0;
            for (int i = ops.at(k+1) - 1; i <= ops.at(k+2) - 1; ++i)
            {
                currval = weights.at(i);
                if(max < currval)
                    max = currval;
            }
            cout << max << endl;
        }
        else
            cout << "Unknown operations." << endl;
    }

    return 0;
}
