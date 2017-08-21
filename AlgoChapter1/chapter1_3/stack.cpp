#include <iostream>
#include <memory>  // for allocator
#include <vector>

using namespace std;

template<typename T>
class ResizingArrayStack
{
	public:
		typedef T data_t;
		//ResizingArrayStack() = default;
		ResizingArrayStack(size_t s):N(s)
		{
			elements = alloc.allocate(N);
			first_free = elements;
		}
		~ResizingArrayStack();

		bool isEmpty(){return first_free == elements;}
		size_t size(){return first_free - elements;}
		void push(data_t d)
		{
			if(size() == 0 || size() == N)
				resize(2 * N);
			alloc.construct(first_free++, d);
		}
		data_t pop()
		{
			return *(--first_free);
		}
		data_t *begin() const
		{
			return elements;
		}
		data_t *end() const
		{
			return first_free;
		}
	private:
		int N = 0;
		allocator<data_t> alloc;
		data_t *elements, *first_free;
		void resize(size_t si);
		void free();  // destroy elements and release memory
};

template <typename T>
void ResizingArrayStack<T>::resize(size_t si)
{
	si==0 ? N : si;
	data_t *temp = alloc.allocate(si);   // allocate 2 * N memory size
	first_free = uninitialized_copy(elements, first_free, temp);
	elements = temp;
}

template <typename T>
void ResizingArrayStack<T>::free()
{
	if(elements)
	{
		for(auto p = first_free; p != elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, size());
	}
}

template <typename T>
ResizingArrayStack<T>::~ResizingArrayStack()
{
	free();
}

// main function for test
int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	ResizingArrayStack<int> test(5);
	test.push(1);

	cout << test.pop() << endl;

	return 0;
}

