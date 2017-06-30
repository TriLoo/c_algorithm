#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;
using  std::placeholders::_1;

void printVec(const vector<string> &words)
{
	for(auto it : words)
		cout << it << endl;
}

void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());

	auto end_unique = unique(words.begin(), words.end());

	cout << "After unique : " << endl;
	printVec(words);

	words.erase(end_unique, words.end());

	cout << "After delete the repeated values: " << endl;
	printVec(words);
}

bool isShort(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

bool check_size(const string &s1, const int sz)
{
	return s1.size() >= sz;
}

ostream &print(ostream & os, const string &s, char c)
{
	return os << s << c << endl;
}

int main(void)
{
	vector<int> vec;
	auto it = back_inserter(vec);

	*it = 42;

	for(auto output : vec)
		cout << output << endl;

	vector<int> vecFill(10, 1);
	fill_n(vecFill.begin(), 10, 0);

	vector<string> str = {"fox", "jumps", "over", "quick", "red", "slow", "red", "the", "the", "turtle"};

	cout << "before unique:" << endl;
	printVec(str);

	elimDups(str);

	cout << "after sort by lenght..." << endl;
	stable_sort(str.begin(), str.end(), isShort);
	printVec(str);

	vector<string> snew(str); 

	int sz = 5;
	// test for lambda version
	cout << "test for lmbda callable state " << endl;
	auto  wc = find_if(str.begin(), str.end(), [sz](const string &a){return a.size() >= sz;});
	for_each(wc, str.end(), [](const string &s){cout << s << endl;});

	// test for mutable
	int count = 0;
	//for_each(wc, str.end(), [count, sz](const string &s)mutable{if(s.size() > sz) ++count;});
	for_each(wc, str.end(), [&count](const string &s){++count;});
	cout << "Count = " << count << endl;

	// Test for bind
	cout << "test for bind " << endl;
	auto g = bind(check_size, _1, sz);
	auto bindWc = find_if(snew.begin(), snew.end(), g);
	//auto bindWc = find_if(snew.begin(), snew.end(), bind(check_size, _1, 5));
	//for_each(bindWc, snew.end(), [](const string &s){cout << s << endl;});            // Version 1
	for_each(bindWc, snew.end(), bind(print, ref(cout), _1, ' '));                      // Version 2

	// test the lambda
	cout << "test for lambda again..." << endl;
	int a = 1;
	int b = 1;
	auto f = [a, b]() -> int {if(a > 0) return a + b;};
	auto c = f();
	cout << "c = " << c << endl;

	return 0;
}

