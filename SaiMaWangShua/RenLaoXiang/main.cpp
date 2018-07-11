#include <iostream>
#include <vector>

/**
 * 典型的Union-Find算法： 一对整数之间具有：自反性，对称性，传递性
 */

using namespace std;

class UF
{
public:
    UF(int n, int m): n_(n), m_(m)
    {
        id = vector<int> (n+1, 0);
        for (int i = 0; i < n+1; ++i)
            id.at(i) = i;
    }

    int find(int p)
    {
        while(p != id[p])
            p = id[p];

        return p;
    }

    void union_f(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        if(pRoot == qRoot)
            return ;
        id[qRoot] = pRoot;
    }

    bool connected(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);

        return pRoot == qRoot;
    }

    int count(int root = 1)
    {
        int tempC = 0;
        for (int i = 1; i < n_ + 1; ++i)
        {
            if(connected(i, root))
                ++tempC;
        }

        return tempC - 1;
    }

private:
    int n_;
    int m_;
    vector<int> id;
};


int main() {
    //std::cout << "Hello, World!" << std::endl;
    int n, m;
    cin >> n >> m;

    int a, b;
    while((n != 0) || (m != 0))
    {
        UF uf(n, m);
        for (int i = 0; i < m; ++i)
        {
            cin >> a >> b;
            uf.union_f(a, b);
        }

        cout <<  uf.count() << endl;

        cin >> n >> m;
    }

    return 0;
}

