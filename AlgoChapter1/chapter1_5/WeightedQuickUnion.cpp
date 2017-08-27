#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
	public:
		UnionFind(int N):count(N), len(N), id(new int [N]), sz(new int [N])
		{
			for(int i = 0; i < N; ++i)
			{
				id[i] = i;
				sz[i] = 1;
			}
		}
		~UnionFind()
		{
			delete [] id;
			delete [] sz;
		}

		int find(int p);
		void WeightedQuickUnionQF(int p, int q);
		bool connected(int p, int q);
		void printCount()
		{
			cout << "count = " << count << endl;
		}
		void printSZ()
		{
			for(int i = 0; i < len; i++)
				cout << "i = " << i << "; sz = " << sz[i] << endl;
		}

		void print()
		{
			for(int i = 0; i < len; ++i)
				cout << "i = " << i << "; id = " << id[i] << endl;
		}
	private:
		int count = 0;
		int len = 0;
		int *id;
		int *sz;
};

int UnionFind::find(int p)
{
	while(p != id[p])
		p = id[p];

	return p;
}

bool UnionFind::connected(int p, int q)
{
	return find(p) == find(q);
}

void UnionFind::WeightedQuickUnionQF(int p, int q)
{
	int pID = find(p);
	int qID = find(q);

	if(pID == qID)
		return;

	int pSZ = sz[pID];
	int qSZ = sz[qID];

	if(pSZ < qSZ)
	{
		id[pID] = qID;
		sz[qID] += sz[pID];
	}
	else
	{
		id[qID] = pID;
		sz[pID] += sz[qID];
	}

	count--;
}

int main(int argc, char **argv)
{

	UnionFind qf(10);
	qf.printCount();
	cout << "--------------SIZE-----------------" << endl;
	qf.printSZ();
	qf.WeightedQuickUnionQF(1, 2);
	cout << "---------------OLD ID-----------------" << endl;
	qf.print();
	qf.WeightedQuickUnionQF(2, 3);
	qf.WeightedQuickUnionQF(4, 2);
	qf.WeightedQuickUnionQF(5, 1);
	qf.WeightedQuickUnionQF(7, 8);
	qf.printCount();
	cout << "---------------NEW ID-----------------" << endl;
	qf.print();
	cout << "--------------SIZE-----------------" << endl;
	qf.printSZ();

	return 0;
}

