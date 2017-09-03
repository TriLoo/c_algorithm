#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <stack>

using namespace std;

// class PriotyQue
// From big to small
template <typename T>
class MaxPQ
{
	public:
		MaxPQ() = default;
		//MaxPQ(int m):data(vector<T>(m)){}
		MaxPQ(vector<T> &a);
		void insert(T v);
		T max();
		T delMax();
		bool isEmpty();
		int size();
	private:
		int N = 0;
		vector<T> data;
		void exch(T &a, T &b);
		bool less(T &a, T &b);
};

template <typename T>
MaxPQ<T>::MaxPQ(vector<T> &a)
{
	for(auto ele : a)
		data.push_back(ele);
}

template <typename T>
bool MaxPQ<T>::less(T &a, T &b)
{
	return a < b;
}

template <typename T>
void MaxPQ<T>::exch(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
void MaxPQ<T>::insert(T v)
{
	data.push_back(v);
	N++;
	for(int i = N - 1; i >=1 && less(data[i-1], data[i]); --i)
		exch(data[i], data[i-1]);
}

template <typename T>
T MaxPQ<T>::delMax()
{
	T val = data[N--];

	return val;
}

template <typename T>
bool MaxPQ<T>::isEmpty()
{
	return N == 0;
}

template <typename T>
int MaxPQ<T>::size()
{
	return N;
}


int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	// get the min M elements from inputting
	MaxPQ<int> mp;

	// get the number of M
	int M = stoi(string(argv[1]));
	int t = 0;

	while(cin >> t)
	{
		mp.insert(t);
		if(mp.size() > M)
			mp.delMax();
	}

	stack<int> st;
	while(!mp.isEmpty())
		st.push(mp.delMax());

	cout << "Min M elements..." << endl;

	while(!st.empty())
	{
		cout << st.top() << endl;
		st.pop();
	}

	return 0;
}

