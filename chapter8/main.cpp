#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct PersonInfo
{
	string name;
	vector<string> phones;
};

int main(int argc, char **argv)
{
	/*   // Correct, read and write from/to file
	string s(argv[1]);

	ifstream ifile;
	ifile.open(s, ifstream::in);

	string text;

	ifile >> text;           // cannot read blackspace

	cout << "text = " << text << endl;

	ofstream ofile;
	ofile.open(s+"out", ofstream::out|ofstream::app);

	ofile << text << endl;

	ifile.close();
	ofile.close();
	*/

	string line, word;
	vector<PersonInfo> people;

	// input person informatioin
	while(getline(cin, line))
	{
		PersonInfo info;
		istringstream is(line);   // bind the string stream to a string
		is >> info.name;
		while(is >> word)
			info.phones.push_back(word);

		people.push_back(info);

	}

	cout << "output of people: " << endl;

	// output person information

	for(auto person : people)
	{
		ostringstream os;
		//cout << "TEST " << person.name << endl;
		for(auto num : person.phones)
			os << " " << num;

		cout << person.name << ", " << os.str() << endl;
	}
	
	return 0;
}
