#include <iostream>

using namespace std;

template <typename K, typename V>
class Node
{
	public:
		typedef Node<K, V>* NodePtr;
		Node() = default;
		Node(K key, V val, NodePtr np):keyVal(key), Value(val), next(np){}
		K keyVal;
		V Value;
		NodePtr next = NULL;
	private:
};

template <typename K, typename V>
class ST
{
	public:
		ST() = default;

		void put(K key, V val);
		V get(K key);
		void deleteItem(K key);

		bool contains(K key)
		{
			return get(key) != NULL;
		}
		bool isEmpty()
		{
			return size() == 0;
		}

		int size()
		{
			return N;
		}
		K min();
		K max();
		K floor(K key);
		K ceiling(K key);

		int rank(K key);
		K select(int k);

		void deleteMin();
		void deleteMax();

		int size(K lo, K hi);
		typename Node<K, V>::NodePtr begin() const;
		typename Node<K, V>::NodePtr end() const;

	private:
		typename Node<K, V>::NodePtr first = NULL;
		//typename Node<K, V>::NodePtr endPtr;
		int N = 0;
};

template <typename K, typename V>
V ST<K, V>::get(K key)
{
	//for(typename Node<T, V>::NodePtr x = first; x != null; x = x->next)
	for(auto x = first; x != NULL; x = x->next)
	{
		if(key == x->keyVal)
			return x->Value;
	}

	cout << "No this Item" << endl;

	return NULL;
}

template <typename K, typename V>
void ST<K, V>::put(K key, V val)
{
	//for()
	//for(auto x = first; x != NULL; x = x->next)
	for(auto x = first; x != NULL; x = x->next)
	{
		if(x != NULL && key == x->keyVal)
		{
			x->Value = val;
			return ;
		}
		first = new Node<K, V>(key, val, first);
		N++;
	}
}


int main(int argc, char **argv)
{
	cout << "hello world" << endl;

	// test sequential search
	ST<string, int> seqseach;
	seqseach.put("hello", 10);

	cout << seqseach.get("hello") << endl;

	return 0;
}

