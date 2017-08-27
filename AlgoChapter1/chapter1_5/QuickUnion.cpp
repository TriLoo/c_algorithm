#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
	public:
		UnionFind(int N):count(N), len(N), id(new int [N])
		{
			for(int i = 0; i < N; ++i)
				id[i] = i;
		}
		~UnionFind()
		{
			delete [] id;
		}

		int find(int p);
		void QuickUnionQF(int p, int q);
		bool connected(int p, int q);
		void printCount()
		{
			cout << "count = " << count << endl;
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

void UnionFind::QuickUnionQF(int p, int q)
{
	int pID = find(p);
	int qID = find(q);

	if(pID == qID)
		return;

	id[qID] = pID;

	count--;
}

int main(int argc, char **argv)
{

	UnionFind qf(10);
	qf.printCount();
	qf.QuickUnionQF(1, 2);
	qf.print();
	qf.QuickUnionQF(2, 3);
	qf.QuickUnionQF(4, 2);
	qf.printCount();
	qf.print();

	return 0;
}
