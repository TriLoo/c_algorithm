#include <iostream>

using namespace std;

class Account
{
	public:
		Account(std::string s, double a):owner(s), amount(a){}
		void calculate(){amount += amount * interestRate;}
		std::string getName(){return owner;}
		double getAmount(){return amount;}
		static double rate() {return interestRate;}
		static void rate(double);
	private:
		std::string owner;
		double amount;
		static double interestRate;
		static double initRate();
};


// initiate and define the static member variables
double Account::interestRate = initRate();

// change the interestRate
void Account::rate(double newRate)
{
	interestRate = newRate;
}

double Account::initRate()
{
	return 0;
}

int main(int argc, char **argv)
{

	Account test("hello", 10);

	cout << "test = " << endl;
	//cout << test.owner << " : " << test.amount << endl;
	cout << test.getName() << " : " << test.getAmount() << endl;

	// after calculate
	test.calculate();
	cout << "After calculate test = " << endl;
	cout << test.getName() << " : " << test.getAmount() << endl;

	// change the interestRate by call the rate();
	//Account::interestRate = 1;     // Not work !!!
	test.rate(1);
	test.calculate();
	cout << "After calculate test = " << endl;
	cout << test.getName() << " : " << test.getAmount() << endl;

	// Not work, because define the same variable twice
	//double Account::interestRate = initRate();

	return 0;
}

