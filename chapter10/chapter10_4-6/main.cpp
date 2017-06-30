#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <functional>
#include <numeric>
#include <string>

using namespace std;

int main(void)
{
	/*
	istream_iterator<int> in(cin), eof;
	cout << accumulate(in, eof, 0) << endl;
	*/
	vector<string> vec = {"hello", "world", "smher"};
	ostream_iterator<string> os(cout, ":");
	for(auto e : vec)
		*os++ = e;
		//os = e;    // seam function as above line
	cout << endl;

	string str = "hello, world. smher";
	//auto comma = str.find_first_of(",.");
	//auto comma = find(str.cbegin(), str.cend(), ',');
	//cout << string(str.cbegin(), comma) << endl;
	cout << string(str.cbegin(), str.cend()) << endl;
	cout << string(str.crbegin(), str.crend()) << endl;

	// read from a file and store it to a vector<string>
	vector<string> text;
	ifstream ifstr;
	ifstr.open("hello");
	istream_iterator<string> osf(ifstr);
	istream_iterator<string> eof;
	while(osf != eof)
	{
		text.push_back(*osf++);
	}
	for(auto e : text)
		cout << e << endl;

	ifstr.close();

	return 0;
}

