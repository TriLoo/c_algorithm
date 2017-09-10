#include <iostream>
#include <stdexcept>

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
		/*
		int size()
		{
			return N;
		}
		*/
};

template <typename K, typename V>
class BSTree
{
	public:
		typedef Node<K,V>* NodePtr;
		//typedef Node<K, V> Node;
		BSTree(NodePtr np):root(np){}
		~BSTree(){}

		int size(Node<K, V>* node)
		{
			if(node == nullptr)
				return 0;
			else
				return node->N;
		}

		void put(K key, V val);
		V get(K key)
		{
			return get(root, key);
		}

		K min()
		{
			return min(root)->keys;
		}
		K max()
		{
			return max(root)->keys;
		}

		K select(int s)
		{
			return select(root, s)->keys;
		}
		int rank(K key)
		{
			return myrank(root, key);
		}

		void deleteMin()
		{
			deleteMin(root);
		}
		void deleteEle(K key)
		{
			root = deleteEle(root, key);
		}

	private:
		V get(Node<K, V>* x, K key);
		NodePtr put(Node<K, V>* x, K key, V val);
		NodePtr min(Node<K, V>* x);
		NodePtr max(Node<K, V>* x);
		NodePtr select(Node<K, V>* x, int s);
		int myrank(NodePtr x, K key);

		NodePtr deleteMin(NodePtr x);
		NodePtr deleteEle(NodePtr x, K key);

		NodePtr root = nullptr;
};

template<typename K, typename V>
V BSTree<K, V>::get(Node<K, V>* x, K key)
{
	try
	{
		if(x == nullptr)
		{
			cout << "No " << key << " in this Binary Search Tree" << endl;
			throw runtime_error("No This Item");
		}
	}
	catch(runtime_error err)
	{
		cout << err.what() << endl;
		cout << "Try again?" << endl;
		return 0;
	}

	if(x->keys < key)
		return get(x->right, key);
	else if(x->keys > key)
		return get(x->left, key);
	else
		return x->vals;
}

template <typename K, typename V>
Node<K, V>* BSTree<K, V>::put(Node<K, V>* x, K key, V val)
{
	if(x == nullptr)
		return new Node<K, V>(key, val, 1);

	if(x->keys > key)
		x->left = put(x->left, key, val);
	else if(x->keys < key)
		x->right = put(x->right, key, val);
	else
		x->vals = val;

	x->N = size(x->left) + size(x->right);

	return x;
}

template <typename K, typename V>
void BSTree<K, V>::put(K key, V val)
{
	root = put(root, key, val);
}

template <typename K, typename V>
Node<K, V>* BSTree<K, V>::min(Node<K, V>* x)
{
	if(x->left == nullptr)
		return x; 
	else 
		return min(x->left);
}

template <typename K, typename V>
Node<K, V>* max(Node<K, V>* x)
{
	if(x->right == nullptr)
		return x;
	else
		return max(x->right);
}

template <typename K, typename V>
Node<K, V>* BSTree<K, V>::select(Node<K, V> *x, int s)
{
	if(x == nullptr)
		return nullptr;

	int ln = size(x->left);

	if(ln > s)   // the node is in the left child tree
		return select(x->left, s);
	else if(ln < s)
		return select(x->right, s-ln-1);
	else
		return x;
}

template <typename K, typename V>
int BSTree<K, V>:: myrank(Node<K, V> *x, K key)
{
	if(x == nullptr)
		return 0;
	
	if(x->keys > key)
		return myrank(x->left, key);
	else if(x->keys < key)
		return 1 + size(x->left) + myrank(x->right, key);
	else
		return size(x->left);
}

template <typename K, typename V>
Node<K, V>* BSTree<K, V>::deleteMin(Node<K, V>* x)
{
	if(x == nullptr)
		return nullptr;

	if(x->left == nullptr)
	{
		//Node<K, V> *temp = x->right;
		//delete x;
		//return temp;
		return x->right;
	}

	x->left = deleteMin(x->left);

	x->N = size(x->left) + size(x->right) + 1;

	return x;
}

template <typename K, typename V>
Node<K, V> * BSTree<K, V>::deleteEle(Node<K, V> *x, K key)
{
	if(x == nullptr)
		return nullptr;

	if(x->keys > key)
		x->left = deleteEle(x->left, key);
	else if(x->keys < key)
		x->right = deleteEle(x->right, key);
	else
	{
		if(x->right == nullptr)
			return x->left;
		if(x->left == nullptr)
			return x->right;

		Node<K, V>* temp = x;
		x = min(x->right);
		x->right = deleteMin(x->right);
		x->left = temp->left;
	}

	x->N = size(x->left) + size(x->right);

	return x;
}

int main(int argc, char **argv)
{
	cout << "hello world " << endl;

	BSTree<int, string> bst(nullptr);
	string name = "hello";
	//Node <int, string> *root = bst.put(nullptr, 5, "hello");
	bst.put(5, "hello");
	bst.put(4, "world");
	bst.put(3, "efg");
	bst.put(6, "abc");
	bst.put(10, "cdl");

	cout << "------------------" << endl;
	cout << bst.get(10) << endl;

	cout << "select 2" << endl;
	cout << bst.select(2) << endl;

	cout << "rank '10' " << endl;
	cout << bst.rank(10) << endl;
	cout << bst.get(10) << endl;

	cout << "Before delete min" << endl;
	cout << bst.select(0) << endl;

	bst.deleteMin();

	cout << "After delete min" << endl;
	cout << bst.select(0) << endl;

	cout << "Add ele 3" << endl;
	bst.put(3, "efg");

	// delete the '5' : the root node
	bst.deleteEle(5);
	bst.put(10, "abc");

	cout << bst.select(2) << endl;

	return 0;
}

