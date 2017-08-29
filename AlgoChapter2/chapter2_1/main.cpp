/*  Author : smh
 *  Date   : 2017. 08. 28
 */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// from less to bigger
class Sort
{
	public:
		void selectionSort(int *a, int len);   // sort algorithm based on selection
		void insertionSort(int *a, int len);   // sort algorithm based on insertion
		void shellSort(int *a, int len);
		bool isSorted(int *a, int len);
	private:
		void swapS(int *a, int *b);
};

void Sort::swapS(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// sort based on shell : h - insertion
void Sort::shellSort(int *a, int len)
{
	int h = 0;
	while(h < len / 3)
		h = h * 3 + 1;

	while(h >= 1)
	{
		for(int i = h; i < len; ++i)
		{
			for(int j = i; j >= h && a[j] < a[j - h]; j -= h)
				swap(a[j], a[j - h]);
		}
		h /= 3;
	}
}

void Sort::selectionSort(int a[], int len)
{
	int min = a[0];
	for(int i = 0; i < len; ++i)
	{
		min = a[i];
		for(int j = i; j < len; ++j )
		{
			if(min > a[j])
			{
				min = a[j];
				swap(a[i], a[j]);
			}
		}
	}
}

// from small to big
void Sort::insertionSort(int *a, int len)
{
	for(int i = 1; i < len; ++i)
	{
		for(int j = i; j > 0 && a[j] < a[j-1]; --j)
			swap(a[j], a[j-1]);
	}
}

bool Sort::isSorted(int *a, int len)
{
	for(int i = 1; i < len; ++i)
	{
		if(a[i] < a[i-1])
			return false;
	}
	return true;
}

void print(int *a, int len)
{
	for(int i = 0; i < len; ++i)
		cout << "i = " << i << "; a = " << a[i] << endl;
}

int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	// prepare data
	int *data = new int [10];
	for(int i = 0; i < 10; i++)
	{
		if(i < 5)
			data[i] = i;
		else
			data[i] = 15 - i;
	}

	cout << "------------------Before----------------" << endl;
	print(data, 10);

	Sort st;
	/*
	// sort based on selection algorithm
	st.selectionSort(data, 10);
	*/
	// sort based on insertioin algorithm
	//st.insertionSort(data, 10);
	st.shellSort(data, 10);


	cout << "------------------After----------------" << endl;
	assert(st.isSorted(data, 10));
	cout << "Sort based on insertion ..." << endl;
	print(data, 10);

	delete [] data;
	return 0;
}
