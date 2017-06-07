#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main(void)
{
	cout << "enter a line of characters" << endl;
	string lin;
	getline(cin, lin);
	cout << lin << endl;

	int count = 0;
	string s = "Hello world!!!";
	cout << s << endl;
	for(auto i : s)
		if(ispunct(i))
			++count;
	cout << "count = " << count << endl;
	for(auto &i : s)
		i = 'X';

	cout << s << endl;

	string s1;
	cout << s1[0] << endl;

	return 0;
}
