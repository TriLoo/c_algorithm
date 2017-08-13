#include <iostream>
#include <stdexcept>

using namespace std;

class SmallInt
{
	friend ostream& operator<<(ostream &os, SmallInt rhs);
	public:
		SmallInt(int i = 0):val(i)
		{
			if(i < 0 || i > 255)
				throw std::out_of_range("Bad SmallInt value");
		}
		// type conversion
		operator int() const 
		{
			return val;
		}

		int read();
	private:
		std::size_t val;
};

int SmallInt::read()
{
	cout << "this is in read function ..." << endl;
	return val;
}

ostream & operator<<(ostream &os, SmallInt rhs)
{
	os << rhs.read();
}


int main(int argc, char **argv)
{

	SmallInt val(5);

	cout << "Convert from the int to class" << endl;
	cout << val << endl;

	cout << "Convert from the class to int" << endl;
	cout << val + 1 << endl;

}
