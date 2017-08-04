#include <iostream>

using namespace std;

class HasPtr
{
	friend void swap(HasPtr&, HasPtr&);
	public:
		HasPtr(const string &s = string()):ps(new string(s)), i(0), use(new size_t(1)){}
		HasPtr(const HasPtr &rhs):ps(rhs.ps), i(rhs.i), use(rhs.use){++(*use);}
		HasPtr& operator=(const HasPtr &rhs);
		~HasPtr();

		void setInt(int t){i = t;}
		void setString(string t){*ps = t;}
		int readInt(){return i;}
		string readString(){return *ps;}
	private:
		string *ps;
		int i;

		size_t *use;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
	++*rhs.use;
	if(*use == 0)
	{
		delete ps;
		delete use;
	}

	i = rhs.i;
	ps = rhs.ps;
	use = rhs.use;

	return *this;
}
HasPtr::~HasPtr()
{
	if(*use == 0)
	{
		delete ps;
		delete use;
	}
}

inline void swap(HasPtr& lhs, HasPtr& rhs)
{
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}


int main(void)
{
	HasPtr t1("hello");
	t1.setInt(10);
	HasPtr t2(t1);

	t2.setInt(5);
	t2.setString("world");
	
	cout << "t1.i = " << t1.readInt() << endl;
	cout << "t2.i = " << t2.readInt() << endl;
	cout << "t1.i = " << t1.readString() << endl;
	cout << "t2.i = " << t2.readString() << endl;

	t2 = t1;
	cout << "t2.i = " << t2.readInt() << endl;
	cout << "t2.i = " << t2.readString() << endl;

	

	return 0;
}

