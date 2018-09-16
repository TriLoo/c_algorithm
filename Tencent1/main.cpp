#include <iostream>
#include <vector>
#include <set>

using namespace std;

long getMethods(vector<int> &a)
{
    long m = 1;
    int durs = 1;
    auto beg = a.begin();
    while(*beg != 1)
    {
        ++beg;
    }
    while(beg != a.end())
    {
        ++beg;
        if(*beg != 0)
        {
            if(durs == 1)
                continue;
            else
            {
                m *= durs;
                durs = 1;
            }
        }
        else
        {
            ++durs;
        }
    }
    return m;
}


int main() {
    int N;
    cin >> N;

    vector<int> posi(N, 0);
    for (int i = 0; i < N; ++i)
        cin >> posi.at(i);

    cout << getMethods(posi) << endl;

    return 0;
}
