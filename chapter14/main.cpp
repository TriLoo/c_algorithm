#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class StrVec
{
	friend ostream & operator<<(ostream &, const StrVec &);
public:
	//StrVec() = default;
	StrVec():elements(nullptr), first_free(nullptr), cap(nullptr){}
	StrVec(const StrVec &);
	StrVec & operator=(const StrVec&);
	~StrVec();

	string& operator[](size_t n)
	{
		return elements[n];
	}

	// const [] version
	const string& operator[](size_t n) const
	{
		return elements[n];
	}

	void push_back(const std::string &);
	size_t size() const {return first_free - elements;}
	size_t capacity() const{return cap - elements;}
	string *begin() const {return elements;}
	string *end() const {return first_free;}
private:
	string *elements, *first_free, *cap;
	static allocator<string> alloc;
	pair<string*, string *>alloc_n_copy(const string *, const string *);
	void free();
	void reallocate();
	void chk_n_alloc()
	{
		if(size() == capacity()) 
			reallocate();
	}
};

ostream &operator<<(ostream &os, const StrVec &item)
{
	for(auto ele : item)
		os <<  ele << endl;

	return os;
}

allocator<string> StrVec::alloc;

pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e)
{
	auto data = alloc.allocate(e-b);
	return {data, uninitialized_copy(b, e, data)};
}

void StrVec::push_back(const string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

void StrVec::free()
{
	if(elements)
	{
		for(auto p = first_free; p != elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = newdata.second;
	cap = newdata.second;
}

StrVec::~StrVec()
{
	free();
}

StrVec& StrVec::operator=(const StrVec &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;

	return *this;
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;

	auto newdata = alloc.allocate(newcapacity);

	auto dest = newdata;
	auto elem = elements;

	for(size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));

	free();

	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	string name1 = "hello";
	string name2 = "world";
	//StrVec test(name1);
	StrVec test;

	test.push_back(name1);
	test.push_back(name2);

	cout << "The strvec size is " << test.size() << endl;
	for(auto ele : test)
		cout << ele << endl;
	//for(auto start = test.begin(); start < test.end(); start++)
		//cout <<  *start << endl;
	
	cout << "Use the << Operator : " << endl;
	cout << test;

	cout << "test the = operator ... " << endl;
	StrVec svec = test;
	for(auto ele : svec)
		cout << ele <<endl;


	return 0;
}

