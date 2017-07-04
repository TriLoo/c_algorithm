#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main(void)
{
	map<string, size_t> word_count;
	string word;
	/*
	while(cin >> word)
		++word_count[word];
	*/
	while(cin >> word)
	{
		auto ret = word_count.insert({word, 1});
		if(!ret.second)
			++ret.first->second;
	}

	auto map_it = word_count.begin();
	map_it->second = 4;
	while(map_it != word_count.cend())
	{
		cout << map_it->first << " : " << map_it->second << endl;
		++map_it;
	}

	for(auto &e : word_count)
		cout << "first: " << e.first << " second : " << e.second << endl;

	multimap<string, string> authors;
	authors.insert({"Barth", "Sot-Weed Factor"});
	authors.insert({"Barth", "Lost in the Funhouse"});
	for(auto &e : authors)
		cout << "first: " << e.first << " second: " << e.second << endl;

	return 0;
}
