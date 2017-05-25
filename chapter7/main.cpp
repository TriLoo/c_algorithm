//#include <iostream>
#include "Sales_data.h"

using namespace std;

int main(int argc, char **argv)
{
	Sales_data A, B;
	/*
	A.bookNo = "hello";
	A.units_sold = 10;
	A.revenue = 4;

	B.bookNo = "hello";
	B.units_sold = 20;
	B.revenue = 10;

	cout << A.isbn() << endl;
	cout << A.units_sold << endl;
	A.combine(B);
	cout << A.units_sold << endl;
	cout << A.revenue << endl;
	cout << A.avg_price() << endl;
	*/

	//istream& is = cin;
	//ostream& os = cout;
	cout << " enter a sale_data data ..." << endl;
	read(cin, A);
	print(cout, A);

	Sales_data C(cin);
	cout << "C = " << endl;
	print(cout, C);

	Sales_data D("hello", 10, 5);
	cout << "D = " << endl;
	print(cout, D);

	string test = "hello";
	D.combine(test);

	return 0;
}
