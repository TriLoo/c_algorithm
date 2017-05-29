#include <iostream>

using namespace std;

class Base
{
	public:
		Base(const string& name):basename(name){}
		string name() {return basename;};
		virtual void print(ostream &os){os << basename;}
	private:
		string basename;
};

class Derived:public Base
{
	public:
		Derived(const string& name, int in):Base(name),i(in){}
		void print(ostream &os){Base::print(os); os << " " << i << endl;;}
		//void print(ostream &os){os << " " << basename;}
	private:
		int i;
};

int main(void)
{
	Base test("hello");
	Derived dev("new", 10);

	dev.print(cout);

	//cout << dev.print(cout) << endl;


	return 0;
}
