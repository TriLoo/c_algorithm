#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <new>
#include <stdexcept>

using namespace std;

class strBlobPtr;

class strBlob
{
	friend class strBlobPtr;
	public:
		typedef vector<string>::size_type size_type;
		strBlob();
		strBlob(initializer_list<string> il);

		void push_back(const string &t){data->push_back(t);}
		void pop_back();

		size_type size() {return data->size();}
		bool empty() {return data->empty();}

		//strBlobPtr begin(){return strBlobPtr(*this);}
		//strBlobPtr end(){auto ret = strBlobPtr(*this, data->size());return ret;}
		strBlobPtr begin();
		strBlobPtr end();

		string& front();
		string& back();
		string& front() const;
		string& back() const;

	private:
		shared_ptr<vector<string>> data;
		void check(size_type i, const string &msg) const;
};

strBlob::strBlob():data(make_shared<vector<string>>())
{
}

strBlob::strBlob(initializer_list<string> il):data(make_shared<vector<string>>(il))
{
}

void strBlob::check(size_type i, const string &msg) const
{
	if(i >= data->size())
		throw out_of_range(msg);
}

string &strBlob::front()
{
	check(0, "front on empty strBlob ...");
	return data->front();
}

string &strBlob::back()
{
	check(0, "front on empty strBlob ...");
	return data->back();
}

string &strBlob::front() const
{
	check(0, "front on const empty strBlob ...");
	return data->front();
}

string &strBlob::back() const
{
	check(0, "back on const empty strBlob ...");
	return data->back();
}

void strBlob::pop_back()
{
	check(0, "pop_back on empty strBlob...");
	data->pop_back();
}

class strBlobPtr
{
	public:
		strBlobPtr():curr(0){}
		strBlobPtr(strBlob &a, size_t sz = 0):wptr(a.data), curr(sz){}
		string &deref() const;
		strBlobPtr& incr();
	private:
		shared_ptr<vector<string>>
			check(size_t, const string &) const;
		weak_ptr<vector<string>> wptr;
		size_t curr;
};

strBlobPtr strBlob::begin()
{
	return strBlobPtr(*this);
}

strBlobPtr strBlob::end()
{
	return strBlobPtr(*this, data->size());
}

shared_ptr<vector<string>> strBlobPtr::check(size_t i, const string &msg) const
{
	auto ret = wptr.lock();
	if(!ret)
		throw runtime_error("unbound strblobptr ...");
	if(i >= ret->size())
		throw out_of_range(msg);

	return ret;
}

string &strBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

strBlobPtr &strBlobPtr::incr()
{
	check(curr, "Increment past end of strBlobPtr ...");
	++curr;
	return *this;
}



void process(shared_ptr<int>ptr)
{
	cout << *ptr << endl;
	cout << ptr.use_count() << endl;
}

int main(void)
{
	shared_ptr<string> p1 = make_shared<string>("hello");
	/*
	if(p1 && p1->empty())
		p1 = make_shared<string>("hello");
		*/
		//*p1 = "hello";
	cout << *p1 << endl;
	shared_ptr<string> p2 = make_shared<string>(10, 'a');
	cout << *p2 << endl;

	p2 = p1;
	cout << "use count: " << p1.use_count() << endl;

	try
	{
		cout << "Test ..." << endl;
		if(p2.use_count() == 0)
			throw out_of_range("The pointer is empty...");
	}
	catch(out_of_range msg)
	{
		cerr << msg.what() << endl;
	}

	strBlob b1;
	{
		strBlob b2 = {"a", "an", "the"};
		b1 = b2;
		b2.push_back("about");
		cout << "size of b2 " << b2.size() << endl;
	}

	//cout << "size of b2 " << b2.size() << endl;      // Wrong, the b2 is not declared here
	cout << "size of b1 " << b1.size() << endl;

	// Test for allocate const memory 
	const int *p_int = new const int(1024);
	cout << "*p_int = " << *p_int << endl;
	delete p_int;

	// Test for process function
	//int *x (new  int (1024));
	shared_ptr<int> x(new int(42));
	process(shared_ptr<int>(x));
	cout << x.use_count() << endl;

	// use nothrow
	int *y = new (nothrow) int(32);
	delete y;

	// Test for new array
	unique_ptr<int[]> up(new int [10]);
	up.release();

	shared_ptr<int> sp(new int [10], [](int *p){delete [] p;});
	for(size_t i = 0; i != 10; i++)
	{
		*(sp.get() + i) = i;
		cout << *(sp.get() + i) << endl;
	}
	sp.reset();


	return 0;
}
