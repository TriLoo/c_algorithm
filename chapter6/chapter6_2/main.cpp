#include <iostream>
#include <initializer_list>

using namespace std;

size_t find_char(const string &s, char c, size_t &occurs)
//size_t find_char( string &s, char c, size_t &occurs)   // Invalid initializatioin of non-const reference of type ...
//size_t find_char(string s, char c, size_t &occurs) // Correct ! because the s is not a reference
{
	auto ret = s.size();
	occurs = 0;
	for(decltype(ret) i = 0; i != s.size(); i++)
	{
		if(s[i] == c)
		{
			if(ret == s.size())
				ret = i;
			occurs++;
		}
	}

	return ret;
}
/*
size_t find_char(const string *s, char c, size_t &occurs)   // cannot convert 'const char *' to const string*
{
	auto ret = s->size();
	occurs = 0;
	for(decltype(ret) i = 0; i != s->size(); ++i)
	{
		if((*s)[i] == c)
		{
			if(ret == s->size())
				ret = i;
			occurs++;
		}
	}

	return ret;
}
*/

int ptr(int *a)
{
	int c = 0; 
	a = &c;
}

int swap(int *a, int b)
{
	int c = 0;
	c = *a;
	*a = b;
	b = c;

	return b;
}

void swap(int *a, int *b)
{
	int *c = a;
	a = b;
	b = c;

	//return b;
}

int sum_il(initializer_list<int> il)
{
	int sum = 0;
	for(auto beg = il.begin(); beg != il.end(); beg++)
	{
		sum += *beg;
	}

	return sum;
}

int sum(int a, ...)
{
	return a;
}

int main(void)
{
	int a = 1, b = 2;
	int c = 3;
	int *p = &c;

	b = swap(p, b);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "p = " << p << endl;
	cout << "*p = " << *p << endl;

	ptr(p);

	cout << "p = " << p << endl;
	cout << "*p = " << *p << endl;


	size_t count;
	auto t = find_char("hello world", 'o', count);
	cout << "count = " << count << " t = " << t << endl;

	initializer_list<int> il{1, 2, 3, 4, 5};
	int sum = sum_il(il);
	cout << "sum = " << sum << endl;

	return 0;
}
