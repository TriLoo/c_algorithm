#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>

using namespace std;

// need to upset the array before apply the quick sort algorithm
//
void print(int *a, int len)
{
	for(int i = 0; i < len; ++i)
		cout << "data = " << a[i] << endl;
}

class Sort
{
	public:
		Sort(int r = 1):N(r){}
		~Sort(){}
		/*
		Sort(int r = 1):N(r), id(new int [N])
		{
			for(int i = 0; i < r; ++i)
				id[i] = i;
		}
		~Sort()
		{
			delete [] id;
		}
		*/

		//friend void print(int *a, int len);
		void shuffle(int *a, int len);    // upset the input array
		int Partion(int *a, int lo, int hi);
		void quickSort(int *a, int lo, int hi);
		void triquickSort(int *a, int lo, int hi);
	private:
		void exch(int &a, int &b);
		int N;
		//int *id;
};

void Sort::exch(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Sort::shuffle(int *a, int len)
{
	// declare the random engine
	// time(0) is the seed of engine
	static default_random_engine e(time(0));
	// declare the distribution function
	static uniform_int_distribution<int> u(0, 1000);

	//cout << "random data:" << endl;
	for(int i = len - 1; i >= 0; --i)
	{
		// 随机数生成
		int rad = u(e) % 10;
		//cout << "rad = " << rad << endl;
		exch(a[i], a[rad]);
	}
}

int Sort::Partion(int *a, int lo, int hi)
{
	// use the first element as the partion element
	int i = lo, j = hi + 1;
	int v = a[lo];
	while(true)
	{
		while(a[++i] < v) 
			if(i == hi)
				break;
		while(a[--j] > v)
			if(j == lo)
				break;
		if(i >= j)
			break ;
		exch(a[i], a[j]);
	}

	exch(a[lo], a[j]);
	return j;
}

void Sort::quickSort(int *a, int lo, int hi)
{
	if(lo >= hi)
		return ;

	int j = Partion(a, lo, hi);
	quickSort(a, lo, j - 1);
	quickSort(a, j + 1, hi);
}

void Sort::triquickSort(int *a, int lo, int hi)
{
	if(lo >= hi)
		return ;

	int lt = lo, i = lo + 1, gt = hi;
	int v = a[lo];
	while(i <= gt)
	{
		if(a[i] < v)
			exch(a[i++], a[lt++]);
		else if(a[i] > v)
			exch(a[gt--], a[i]);
		else   // a[i] == v, i++
			i++;
	}
	triquickSort(a, lo, lt-1);
	triquickSort(a, gt+1, hi);
}

int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	int *data = new int [10];
	for(int i = 0; i < 10; ++i)
	{
		if(i < 5)
			data[i] = i;
		else
			data[i] = 15 - i;
	}

	cout << "Input data ..." << endl;
	print(data, 10);

	Sort st(10);
	// upset input array
	st.shuffle(data, 10);

	cout << "After shuffle ..." << endl;
	print(data, 10);

	//st.quickSort(data, 0, 9);
	st.triquickSort(data, 0, 9);
	cout << "After quick sort ..." << endl;
	print(data, 10);

	return 0;
}

