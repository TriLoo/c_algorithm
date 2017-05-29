#include "quote.h"

using namespace std;

int main(void)
{
	Quote test("hello", 1);
	double a = 10;
	size_t b = 10;
	double c = 0.8;
	string s = "Hello new" ;
	BulkQuote testNew(s, a, b, c);

	//Quote &ref = testNew;
	Quote *ref;
	ref = &testNew;

	cout << test.isbn() << " " << test.net_price(5) << endl;

	cout << "call from the new class:" << endl;
	cout << testNew.net_price(12) << endl;;

	cout << "call from the basic class:" << endl;
	cout << ref->net_price(12) << endl;
	cout << "call from the basic class:" << endl;
	cout << testNew.net_price(3) << endl;
	cout << testNew.isbn() << endl;

	cout << "test for dirved class call the basic funtion" << endl;
	cout << testNew.Quote::net_price(12) << endl;
	//cout << "the ref call the dirved version " << endl;         // Error, bulkquote is not a base of quote
	//cout << ref->BulkQuote::net_price(12) << endl;

	cout << "---------" << endl;
	cout << testNew.net_price(3) << endl;

	// for test
	//Disc_quote testDQ;


	return 0;
}
