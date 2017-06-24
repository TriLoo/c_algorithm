#include <iostream>
#include <string>
#include <sstream>
#include <utility>

using namespace std;


template <typename T>
string debug_rep(const T &t)
{
	ostringstream ret;
	ret << t;
	return ret.str();
}

template <typename T>
ostream &print(ostream &os, const T &t)
{
	return os << t;
}

template <typename T, typename... args>
ostream &print(ostream &os, const T &t, const args&... reset)
{
	os << t;
	cout << endl << sizeof...(args) << endl;
	return print(os, debug_rep(reset)...);
}

/*
template <typename T, typename... args>
ostream &print(ostream &os, const T &t, const args&... reset)
{
	os << t;
	cout << endl << sizeof...(args) << endl;
	return print(os, reset...);
}
*/

template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void g(int &&i, int &j)
{
	cout << i << " " << j << endl;
}

int main(void)
{

	int i = 10;
	flip(g, i, 21);
	
	cout << "test debug rep" << endl;
	cout << debug_rep<int>(i) << endl;

	string s("hello");
	print(cout,i,  s, 31);

	return 0;
}
