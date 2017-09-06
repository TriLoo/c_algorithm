#include <iostream>
#include <vector>

using namespace std;

/*
// K : key   type
// V : value type
template <typename K, typename V>
class Node
{
	public:
		typename Node<K, V>* NodePtr;
		Node(K ke, V va, NodePtr p):key(ke), val(va), next(p){}
		K key;
		V val;
		NodePtr next = nullptr;
};
*/

// From small to big
template <typename K, typename V>
class BinarySearchST
{
	public:
		//typedef	typename Node<K, V>::NodePtr NodePtr;
		//typedef	Node<K, V>::NodePtr NodePtr;         // don't need typename
		BinarySearchST() = default;
		BinarySearchST(int sz):N(0), len(sz), Key(new K [sz]), Val(new V [sz]){}
		~BinarySearchST()
		{
			delete []  Key;
			delete [] Val;
		}

		void put(K ke, V va);
		V get(K ke);

		bool isEmpty()
		{
			return N == 0;
		}

		int size()
		{
			return N;
		}

		int rank(K ke);
		
		K min()
		{
			return Key[0];
		}

		K max()
		{
			return Key[N - 1];
		}

		K select(int k)
		{
			return Key[k];
		}

	private:
		//NodePtr first = nullptr;
		K *Key;
		V *Val;
		int N = 0;
		int len = 0;
};

// rank based on Interation
template <typename K, typename V>
int BinarySearchST<K, V>::rank(K ke)
{
	int lo = 0, hi = N - 1;
	while(lo <= hi)
	{
		int mid = lo + (hi - lo) / 2;
		if(ke < Key[mid])
			hi = mid - 1;
		else if(ke > Key[mid])
			lo = mid + 1;
		else
			return mid;
	}

	return lo;   // used for add new item at correct position
}

// rank based on recursively calling rank

template <typename K, typename V>
V BinarySearchST<K, V>::get(K ke)
{
	if(isEmpty())
		return 0;
	int i = rank(ke);
	if(i < N && Key[i] == ke)
		return Val[i];
	else
	{
		cout << "No this item ..." << endl;
		return 0;
	}
}

template <typename K, typename V>
void BinarySearchST<K, V>::put(K ke, V va)
{
	int i = rank(ke);
	if(i < N && Key[i] == ke)
	{
		Val[i] = va;
		return ;
	}

	for(int j = i; j < N; j++)
	{
		Key[j+1] = Key[j];
		Val[j+1] = Val[j];
	}
	Key[i] = ke;
	Val[i] = va;
	N++;
	if(N >= len - 1)
	{
		len *= 2;
		K *KeyTemp = new K [len];
		V *ValTemp = new V [len];
		for(int i = 0; i < N; ++i)
		{
			KeyTemp[i] = Key[i];
			ValTemp[i] = Val[i];
		}
		K *tempK = Key;
		V *tempV = Val;
		Key = KeyTemp;
		Val = ValTemp;
		
		delete [] tempK;
		delete [] tempV;
	}
}

int main(int argc, char **argv)
{
	cout << "hello world " << endl;

	BinarySearchST<string, int> st(10);
	st.put("hello", 10);
	cout << "size = " << st.size() << endl;
	st.put("world", 11);
	cout << "size = " << st.size() << endl;
	st.put("abc", 1);
	cout << "size = " << st.size() << endl;
	st.put("bcd", 2);
	cout << "size = " << st.size() << endl;
	st.put("efg", 3);
	cout << "size = " << st.size() << endl;
	st.put("hig", 4);
	cout << "size = " << st.size() << endl;
	st.put("jkl", 5);
	cout << "size = " << st.size() << endl;
	st.put("klm", 6);
	cout << "size = " << st.size() << endl;
	st.put("lmn", 7);
	cout << "size = " << st.size() << endl;
	st.put("mno", 8);
	cout << "size = " << st.size() << endl;
	st.put("nop", 9);
	cout << "size = " << st.size() << endl;

	cout << "Test for get()" << endl;
	cout << st.get("mno") << endl;

	return 0;
}

