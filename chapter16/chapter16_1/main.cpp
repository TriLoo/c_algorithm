#include "head.h"

int main(int argc, char **argv)
{
	string s1 = "hello";
	string s2 = "helle";

	int i = compare(s1, s2);

	cout << "result = " << i << endl;

	// test for template class Blob
	Blob<string> testBlob = {"hello", "World"};

	cout << testBlob.size() << endl;

	for(int i = 0; i < testBlob.size(); ++i)
	{
		cout << testBlob[i] << endl;
	}

	return 0;
}
