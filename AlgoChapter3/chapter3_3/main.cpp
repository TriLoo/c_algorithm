#include <iostream>

using namespace std;

#define RED true
#define BLACK false

template <typename K, typename V>
class Node
{
	public:
		typedef Node<K, V>* NodePtr;
		Node(K key, V val, int n, bool col):keys(key), vals(val), N(n), color(col){}

		K keys;
		V vals;
		int N = 0;
		bool color = BLACK;   // the black side
		NodePtr left = nullptr, right = nullptr;

	private:
};

template <typename K, typename V>
class RBTree               // red black tree
{
	public:
		typedef Node<K, V>* NodePtr;
		RBTree(){}
		~RBTree(){}

		NodePtr rotateLeft(NodePtr h);   // h is the old child root, return new child root
		NodePtr rotateRight(NodePtr h);   // h is the old child root, return new child root

		bool isRed(NodePtr x)
		{
			if(x == nullptr)
				return false;
			
			return x->color == RED;
		}

		int size(NodePtr x)
		{
			if(x == nullptr)
				return 0;
			
			return x->N;
		}

		void filpColor(NodePtr h);

		void put(K key, V val)
		{
			root = put(root, key, val);
		}

		V get(K key)
		{
			return get(root, key);
		}

	private:
		NodePtr put(NodePtr x, K key, V val);
		V get(NodePtr x, K key);
		NodePtr root = nullptr;
};

template <typename K, typename V>
Node<K, V>* RBTree<K, V>::rotateLeft(NodePtr h)
{
	NodePtr x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;

	x->N = h->N;
	h->N = 1 + size(x->left) + size(x->right);

	return x;
}

template <typename K, typename V>
Node<K, V>* RBTree<K, V>::rotateRight(NodePtr h)
{
	NodePtr x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;

	x->N = h->N;
	h->N = 1 + size(x->left) + size(x->right);

	return x;
}

template <typename K, typename V>
void RBTree<K, V>::filpColor(NodePtr h)
{
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
}

template <typename K, typename V>
Node<K, V>* RBTree<K, V>::put(NodePtr x, K key, V val)
{
	if(x == nullptr)
		return new Node<K, V>(key, val, 1, RED);   // the insert is always RED

	if(key > x->keys)
		x->right = put(x->right, key, val);
	else if(key < x->keys)
		x->left = put(x->left, key, val);
	else
		x->vals = val;

	if(isRed(x->right) && !isRed(x->left))
		x = rotateLeft(x);
	if(isRed(x->left) && isRed(x->left->left))
		x = rotateRight(x);
	if(isRed(x->left) && isRed(x->right))
		filpColor(x);

	x->N = size(x->left) + size(x->right) + 1;

	return x;
}

template <typename K, typename V>
V RBTree<K, V>::get(NodePtr x, K key)
{
	if(x == nullptr)
		return NULL;

	if(key < x->keys)
		return get(x->left, key);
	else if(key > x->keys)
		return get(x->right, key);
	else
		return x->vals;
}

int main(int argc, char **argv)
{
	cout << "hello world " << endl;

	RBTree<int, string> rbt;
	rbt.put(5, "hello");
	rbt.put(4, "world");
	rbt.put(6, "smh");
	rbt.put(7, "abc");


	cout << rbt.get(5) << endl;
	cout << rbt.get(7) << endl;

	return 0;
}

