#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <stdexcept>
#include <forward_list>

using namespace std;

int main(int argc, char **argv)
{
	/*
	list<deque<int>>  temp{{123}, {567}, {890}};

	deque<int> ele;

	for(auto ou : temp)
	{
		ele = ou;
		for(auto out : ele)
			cout << out << endl;
	}
	list<string> author = {"hello", "world", "C++"};
	vector<const char *> articles = {"a", "an", "che"};

	//deque<string> authList(author);
	deque<string> authList(author.begin(), author.end());

	for(const auto  temp : authList)
		cout << temp << endl;

	array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	array<int, 10> arrB(arr);
	for(const auto arrTemp : arrB)
		cout << arrTemp << endl;
	
	cout << "sizeof(arr.max_size) : " << arr.max_size() << endl;

	if(arr == arrB)
		cout << "arr == arrB" << endl;
	else
		cout << "not equal..." << endl;

	string text;
	deque<string> str;
	deque<string>::iterator strIt = str.begin();
	while(cin >> text)           // Ctrl + D for Linux
		strIt = str.insert(strIt, text);

	for(auto textOut : str)
		cout << textOut << endl;

	vector<string> strvec;
	try{
		cout << strvec.at(0);
	}
	catch(out_of_range err)    // catch must have the big brace { and }
	{
		cout << "out of range of strvec" << endl;
		cout << err.what() << endl;
	}
	*/

	forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto prev = flst.before_begin();
	auto curr = flst.begin();
	while(curr != flst.end())
	{
		if( * curr %2)
			curr = flst.erase_after(prev);
		else
		{
			prev = curr;
			++curr;
		}
	}

	for(auto temp : flst)
		cout << temp << endl;

	//vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
	//cout << a.capacity() << endl;
	vector<int> a;
	cout << "capacity: " << a.capacity() << " size: " << a.size() << endl;
	for(vector<int>::size_type it = 0; it != 24; it++)
		a.push_back(it);
	cout << "capacity: " <<  a.capacity() << " size: " << a.size() << endl;


	return 0;
}
