#include <iostream>

using namespace std;

template <typename T>
class Bag
{
	public:
		class Node
		{
			public:
				Node(T ele):item(ele){}
				T item;
				Node * next = nullptr;
		};

		void add(T ele);
		Node * begin()
		{
			return first;
		}

		Node* end()
		{
			return first + N;
		}

	private:
		Node* first = nullptr;
		int N = 0;
};

template <typename T>
void Bag<T>::add(T ele)
{
	Node* oldfirst = first;
	first = new Node(ele);
	first->next = oldfirst;
	N++;
}

//template <typename T>
class Graph
{
	public:
		typedef Bag<int>* BagPtr;
		Graph(int v)
		{
			V = v;   // the number of vertexes
			E = 0;
			adj = new BagPtr [v];
			for(int i = 0; i < v; ++i)
				adj[i] = new Bag<int>();
		}
		~Graph()
		{
		}

	private:
		int V = 0;   // number of vertexes
		int E = 0;   // number of edges
		BagPtr* adj = nullptr;
};

int main(int argc, char **argv)
{
	cout << "hello world" << endl;

	Bag<int> bg;
	bg.add(1);
	cout << bg.begin()->item << endl;

	return 0;
}

