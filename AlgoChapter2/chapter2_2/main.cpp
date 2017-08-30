#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Sort
{
	public:
		Sort(int N):aux(new int [N]()), S(N){}
		~Sort()
		{
			if(aux != nullptr)
				delete [] aux;
		}

		void merge(int *a, int lo, int mid, int hi);
		void sortUB(int *a, int lo, int hi);
		void sortBU(int *a, int lo, int hi);
	private:
		void exch(int &a, int &b);
		int *aux;
		int S = 0;
};

void Sort::exch(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

// normal merge sort
// from small to big
void Sort::merge(int *a, int lo, int mid, int hi)
{
	int i = lo, j = mid + 1;
	for(int k = lo; k <= hi; ++k)
		aux[k] = a[k];
	for(int k = lo; k <= hi; ++k)
	{
		if(i > mid)   // the left part exausted
			a[k] = aux[j++];
		else if(j > hi)    // the right part exausted
			a[k] = aux[i++];
		else if(aux[i] < aux[j])   // use the left element
			a[k] = aux[i++];
		else                       // use the right element
			a[k] = aux[j++];
	}
}

// top sort function
// sort UB : Upper to Bottom based on recursive call
void Sort::sortUB(int *a, int lo, int hi)
{
	if(lo >= hi)
		return ;
	int mid = lo + (hi - lo) / 2;
	sortUB(a, lo, mid);
	sortUB(a, mid + 1, hi);
	merge(a, lo, mid, hi);
}
// top sort function
// sort BU : Bottom to Upper
void Sort::sortBU(int *a, int lo, int hi)
{
	for(int sz = 1; sz < S; sz += sz)
		for(int lo = 0; lo < S - sz; lo += 2 * sz)
			merge(a, lo, lo + sz - 1, min(lo + 2 * sz - 1, S - 1));
}

int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	int *data = new int[10];
	for(int i = 0; i < 10; ++i)
	{
		if(i < 5)
			data[i] = i;
		else
			data[i] = 15 - i;
	}

	cout << "-------------Before Sort-------------" << endl;
	for(int i = 0; i < 10; ++i)
		cout << "i = " << i << "; " << data[i] << endl;

	Sort st(10);
	//st.merge(data, 0, 4, 9);
	//st.sortUB(data, 0, 9);
	st.sortBU(data, 0, 9);

	cout << "-------------After Sort-------------" << endl;
	for(int i = 0; i < 10; ++i)
		cout << "i = " << i << "; " << data[i] << endl;

	return 0;
}

