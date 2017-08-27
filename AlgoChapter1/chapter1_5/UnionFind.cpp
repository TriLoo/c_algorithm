#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
	public:
		UnionFind(int N):count(N), len(N), id(new int [N])
		{
			for(int i = 0; i < N; ++i)
			{
				id[i] = i;
			}
		}
		~UnionFind()
		{
			delete [] id;
		}
		void printCount()
		{
			cout << "Count = " << count << endl;
		}
		void print()
		{
			for(int i = 0; i < len; ++i)
				cout << "i = " << i << "; id = " << id[i] << endl;
		}

		void QuickFindUnion(int p, int q);
		int find(int p);
		bool connected(int p, int q)
		{
			return find(p) == find(q);
		}
	private:
		int count = 0;
		int len = 0;
		int *id;
};

// the find function 
int UnionFind::find(int p)
{
	return id[p];
}

// the union function
void UnionFind::QuickFindUnion(int p, int q)
{
	int a = find(p);
	int b = find(q);

	for(int i = 0; i < count; ++i)
	{
		if(b == id[i])
			id[i] = a;
	}
	count--;
}

int main(int argc, char **argv)
{
	UnionFind uf(10);
	uf.printCount();
	uf.print();

	uf.QuickFindUnion(1, 2);
	uf.QuickFindUnion(1, 3);
	uf.QuickFindUnion(4, 1);

	uf.printCount();
	uf.print();

	return 0;
}
