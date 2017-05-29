#include <iostream>

using namespace std;

class Base
{
	public:
		void pub_mem();
	protected:
		int prot_mem;
	private:
		int priv_mem;
};

class Sneaky:public Base
{
	// default to private
	friend void clobber(Sneaky &);
	friend void clobber(Base &);
	int j;
};

void clobber(Sneaky &s)
{
	s.j = s.prot_mem = 0;
}

/*
void clobber(Base &b)
{
	b.prot_mem = 0;
}
*/

class Pub_Derv:public Base
{
	int f() {return prot_mem;}
};

class Prot_Derv:protected Base
{
	int f(){return prot_mem;}
};

class Priv_Derv:private Base
{
	int f() {return prot_mem;}
};

int main(void)
{
	Pub_Derv d1;
	Prot_Derv d2;
	Priv_Derv d3;

	//Sneaky test;
	//test.prot_mem = 0;   //  inaccessable

	//d2.f(); 		// Wrong !! Prot_Derv::f() is private

	Base *p = &d1;
	//p = &d2;   // Same error as next line
	//p = &d3;   // Base is an inaccessable to class Priv_Derv

	return 0;
}
