#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
int compare(const T& s1, const T &s2)
{
	if(s1 < s2)
		return -1;
	else
		return 1;

	return 0;
}

template <typename T>
class Blob
{
	public:
		typedef T value_type;
		typedef typename vector<T>::size_type size_type;

		Blob();
		Blob(std::initializer_list<T> il);

		size_type size() const {return data->size();}
		bool empty() const {return data->empty();}

		void push_back(const T &t) {data->push_back(t);}
		void push_back(T &&t) {data->push_back(std::move(t));}

		void pop_back();

		T& back();
		T& operator[] (size_type i);

	private:
		std::shared_ptr<std::vector<T>> data;
		void check(size_type i, const std::string &msg) const;
};

template <typename T>
Blob<T>::Blob():data(std::make_shared<std::vector<T>>())
{}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il))
{

}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
	if(i >= data->size())
		throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::back()
{
	check(0, "back on empyt Blob");
	return data->back();
}

template <typename T>
T& Blob<T>::operator[] (size_type i)
{
	check(i, "subscript out of range");
	return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back()
{
	check(0, "pop_back on empty Blob");
	data->pop_back();
}

template<typename T>
class BlobPtr
{
	public:
		BlobPtr():curr(0){};
		BlobPtr(Blob<T> &a, size_t sz = 0):wptr(a.data), curr(sz){}

		T& operator*() const
		{
			auto p = check(curr, "deference past end");
			return (*p)[curr];
		}

		BlobPtr& operator++();
		BlobPtr& operator--();
	private:
		std::shared_ptr<std::vector<T>> check(std::size_t, const std::string &) const ;
		std::weak_ptr<std::vector<T>> wptr;
		std::size_t curr;
};

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++ ()
{
	BlobPtr ret = *this;
	++*this;
	return ret;
}

// test for  friend class
template <typename T>
class Base;

template <typename T>
class Third;

template <typename T>
bool operator==(const Third<T> &, const Third<T>&);

template <typename T>
class Third
{
	friend class  Base<T>;
	friend bool operator==<T>(const Third<T>&, const Third<T> &);
};

