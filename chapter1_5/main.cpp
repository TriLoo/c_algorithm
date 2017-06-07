#include <iostream>
#include <stdexcept>

using namespace std;

int t = 0;
constexpr int *cp = &t;   // Right!!!

float divide(float a, float b)
{
	try
	{
		if( b == 0)
			throw runtime_error("the divide is zero !!!") ;
		else
			return a / b;
	}
	catch(runtime_error err)
	{
		cout << " the input is zero and is wrong..." << endl;
		cout << " please input the b again: " << endl;
		float c = 0;
		cin >> c;
		return a / c;
	}


	return 0;
}

int main(void)
{
	int a = 0;
	cout << "a = " << a << endl;
	int  *const p = &a;
	*p = 1;
	cout << "a = " << a << endl;

	//constexpr int *cp = &a;   // Wrong, &a is not a const expression
	
	// test the exception
	float m = 1, n = 0;
	float b = divide(m, n);

	cout << "b = " << b << endl;

	return 0;
}
