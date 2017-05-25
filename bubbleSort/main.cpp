#include <iostream>

using namespace std;

void oddEvenSort(int a[], int n)
{
	int temp = 0;
	for(int i = 0; i < n; i++)
	{
		// Even sort
		for(int j = 0; 2 * j < n; j++)
		{
			if(a[2 * j] > a[2 * j + 1])
			{
				temp = a[2 * j];
				a[2 * j] = a[2 * j + 1];
				a[2 * j + 1] = temp;
			}
		}

		// Odd sort
		for(int j = 1; 2 * j < n; j++)
		{
			if(a[2 * j - 1] > a[2 * j])
			{
				temp = a[2 * j - 1];
				a[2 * j - 1] = a[2 * j];
				a[2 * j] = temp;
			}
		}
	}
}

/*
void bubbleSort(int a[], int n)
{
	int temp = 0;

	for(int i = n; i > 0; i--)
		for(int j = 0; j < i; j++)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j+1];
				a[j+1] = a[j];
				a[j] = temp;
			}
		}
}
*/

int main(int argc, char **argv)
{
	int a[] = {5, 4, 3, 2, 1};
	//bubbleSort(a, 5);
	oddEvenSort(a, 5);
	for(int i = 0; i < 5; i++)
		cout << a[i] << endl;

	return 0;
}

