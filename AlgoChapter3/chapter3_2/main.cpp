#include <iostream>

using namespace std;

template <typename K, typename V>
class Node
{
	public:
		typedef Node<K, V>* NodePtr;
		Node(K key, V val, int n):keys(key), vals(val), N(n), left(nullptr), right(nullptr){}
		K keys;
		V vals;
		NodePtr left, right;
		int N = 1;
};

class BSTree
{
	public:
		typedef Node<K,V>::NodePtr NodePtr;
		typedef Node<K, V> Node;
		BSTree();
		~BSTree();

		int size(Node node)
		{
			return node.N;
		}




	private:
};

int main(int argc, char **argv)
{
	cout << "hello world " << endl;

	return 0;
}
