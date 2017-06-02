#include <iostream>
#include <vector>

using namespace std;

int *reset(int *);
double *reset(double *);

bool str_subrange(const string str1, const string &str2)
{
	if(str1.size() == str2.size())
		return str1 == str2;
	auto size = (str1.size() < str2.size())? str1.size() : str2.size();

	for(decltype(size) i = 0; i != size; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}

	return true;
}

void print(int (&arr)[10])
{
	for(auto elem:arr)
		cout << elem << endl;
}

void print(int *a)
{
	cout << *a << endl;
}

string (*teststring(string (*a)[10]))[10]
{
	return a;
}
//string (&teststring(void)) [10];
auto testString(void)->string (&)[10];

// test for preprocess macro
void testMacro(void)
{
	cout << "in function" << __func__ << endl
		<< " Compiled on :" << __DATE__ << endl
		<< "At : " << __TIME__ << endl
		<< " In FIle :" << __FILE__ << endl
		<< "on" << __LINE__ << " line" << endl;
}

int (*funcP)(int , int);

typedef int(*FuncP)(int, int) ;

int main(void)
{

	int a[2] = {0, 1};
	int b[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	print(a);
	//print(b);
	//
	// test the return of pointer to array
	using Ptr = string [10];
	Ptr *PtrTest;
	string s[10];
	PtrTest = teststring(PtrTest);

	testMacro();

	vector<FuncP> funVec;

	return 0;
}
