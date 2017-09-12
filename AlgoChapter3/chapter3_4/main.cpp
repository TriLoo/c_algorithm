#include <iostream>
#include <vector>

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
		NodePtr next = nullptr;
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

		int size(K lo, K hi);
		typename Node<K, V>::NodePtr begin() const;
		typename Node<K, V>::NodePtr end() const;

	private:
		typename Node<K, V>::NodePtr first = nullptr;
		//typename Node<K, V>::NodePtr endPtr;
		int N = 0;
};

template <typename K, typename V>
V ST<K, V>::get(K key)
{
	//for(typename Node<K, V>::NodePtr x = first; x != null; x = x->next)
	for(typename Node<K, V>::NodePtr x = first; x != nullptr; x = x->next)
	{
		if(key == x->keyVal)
			return x->Value;
	}

	cout << "No this Item" << endl;

	return 0;
}

template <typename K, typename V>
void ST<K, V>::put(K key, V val)
{
	//for()
	//for(auto x = first; x != NULL; x = x->next)
	for(auto x = first; x != nullptr; x = x->next)
	{
		if(x != nullptr && key == x->keyVal)
		{
			x->Value = val;
			return ;
		}
	}
	first = new Node<K, V>(key, val, first);
	N++;
}


template <typename K, typename V>
class SeparateChainingHashST
{
	public:
		typedef ST<K, V>* STPtr;
		SeparateChainingHashST(int m = 37):M(m), st(new STPtr [M])   // st is the two dimension point
		{
			for(int i = 0; i < M; ++i)
				st[i] = new ST<K, V>();
		}

		int hasher(K key)
		{
			return hash<K>()(key);
		}

		V get(K key)
		{
			return st[hasher(key)]->get(key);
		}

		void put(K key, V val)
		{
			st[hasher(key)]->put(key, val);
		}
	private:
		STPtr* st;
		int M = 37;
		int N = 0;
};

template <typename K, typename V>
class LinearProblingHashST
{
	public:
		LinearProblingHashST(int m = 16):M(m),keys(new K [m]), vals(new V [m])
		{
			for(int i = 0; i < m; i++)
			{
				keys[i] = -1;
			}
		}

		int hasher(K key)
		{
			return (hash<K>()(key) & 0x7FFFFFFF) % M;
		}

		void put(K key, V val)
		{
			int i;
			for(i = hasher(key); keys[i] != -1; i = (i+1) % M)
			{
				if(keys[i] == key)
				{
					vals[i] = val;
					return;
				}
			}
			keys[i] = key;
			vals[i] = val;
			N++;
		}

		V get(K key)
		{
			int i;
			for(i = hasher(key); keys[i] != -1; i = (i + 1) % M)
			{
				if(keys[i] == key)
					return vals[i];
			}

			return NULL;
		}
	private:
		int N = 0;
		int M = 16;
		K *keys;        // array storing the Keys
		V *vals;        // array stroing corresponding Vals
};


int main(int argc, char **argv)
{
	cout << "hello world" << endl;

	SeparateChainingHashST<int, string> abc;
	abc.put(1, "hello");
	abc.put(2, "world");
	cout << abc.get(1) << endl;

	cout << "----------------" << endl;

	LinearProblingHashST<int, string> ab;

	ab.put(1, "hello");
	ab.put(2, "hello");
	ab.put(16, "world1");
	ab.put(8, "world2");

	cout << ab.get(8) << endl;

	return 0;
}

