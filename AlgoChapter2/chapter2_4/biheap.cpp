#include <iostream>
#include <vector>

using namespace std;

/*
// class bi-heap used for priority queue
template <typename T>
class biheap
{
	public:
		biheap(int si);

		// floating the k-th element
		void swim(int k);
		void sink(int k);

	private:
		int N = 0;
		vector<T> data;
		bool less(int i, int j);
		void exch(T &a, T &b);
};

template <typename T>
biheap<T>::biheap(int si):N(si), data(vector<T>(si))
{
}

template <typename T>
bool biheap<T>::less(T &a, T &b)
{
	return data[i] < data[j];
}

template <typename T>
void biheap<T>::exch(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
void biheap<T>::swim(int k)
{
	while(less(k/2, k) && k > 1)
	{
		exch(data[k], data[k/2]);
		k = k / 2;
	}
}

template <typename T>
void biheap<T>::sink(int k)
{

}
*/

template <typename T>
class MaxPQ
{
	public:
		MaxPQ() = default;
		MaxPQ(vector<T> &a):N(a.size() - 1),data(a){}               // used for sort
		MaxPQ(int si):N(si), data(vector<T>(1)){}

		bool isEmpty();
		int size()
		{
			return N;
		}
		void insert(T v);
		T delMax();
		void pq_sort();

		void print();
		void print(int n);
	private:
		int N = 0;
		vector<T> data;
		bool less(int i, int j);
		void exch(int i, int j);
		void swim(int k);
		void sink(int k);
};

template <typename T>
bool MaxPQ<T>::isEmpty()
{
	return N == 0;
}

template <typename T>
void MaxPQ<T>::insert(T v)
{
	data.push_back(v);
	N++;
	swim(N);
}

template <typename T>
T MaxPQ<T>::delMax()
{
	T temp = data[1];
	exch(1, N);
	N--;
	sink(1);

	return temp;
}

template <typename T>
bool MaxPQ<T>::less(int i, int j)
{
	return data[i] < data[j];
}

template <typename T>
void MaxPQ<T>::exch(int i, int j)
{
	T temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}

template <typename T>
void MaxPQ<T>::swim(int k)
{
	while(less(k/2, k) && k > 1)
	{
		exch(k/2, k);
		k /= 2;
	}
}

template <typename T>
void MaxPQ<T>::sink(int k)
{
	while(2 * k < N)
	{
		int j = 2 * k;
		if(j < N && less(j, j+1))
			j++;
		if(!less(k, j))
			break;
		exch(k, j);
		k = j;
	}
}

template <typename T>
void MaxPQ<T>::print()
{
	/*
	for(auto e : data)
		cout << e << endl;
	*/

	for(int i = 1; i <= N; i++)
		cout << data[i] << endl;
}


template <typename T>
void MaxPQ<T>::pq_sort()
{
	// Step 1 : struct the bi heap
	for(int k = N / 2; k >= 1; k--)
		sink(k);
	
	// Stepp 2 : sort by calling sink
	while(N > 1)
	{
		data[N] = delMax();
	}
}

template <typename T>
void MaxPQ<T>::print(int n)
{
	for(int i = 1; i < n; ++i)
		cout << data[i] << endl;
}

int main(int argc, char **argv)
{
	cout << "hello world..." << endl;

	MaxPQ<int> pq(0);
	pq.insert(1);
	pq.insert(4);
	pq.insert(3);
	pq.insert(10);
	pq.insert(6);
	pq.insert(12);

	cout << "After insert 6 elements..." << endl;
	pq.print();

	cout << "After delete the max elements ..." << endl;
	pq.delMax();
	pq.print();


	cout << "Test for sort ..." << endl;
	vector<int> d = {0, 5, 4, 3, 2, 1};
	cout << d.size() << endl;

	cout << "Before sort ..." << endl;
	MaxPQ<int> testsort(d);
	testsort.print();

	cout << "After sort ..." << endl;
	testsort.pq_sort();
	testsort.print(d.size());

	return 0;
}

