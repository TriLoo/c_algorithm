/* ***
 * This file include the implementation of Sta(stack), Que(queue) and Bag data
 * structure based on list.
 * In the Bag Algorith, it is just the add element after List structure, so here Not 
 * include this algorithm.
 *
 * What's more, the implementation of Queue may cause Segment Error and I don't know the reason 
 * for now. 
 * ***/
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Node
{
	public:
		typedef T data_t;
		typedef Node<T>* NodePtr;
		data_t item;
		NodePtr next;
};

// implementation of Stack
template<typename T>
class Stack
{
	public:
		typedef T data_t;
		Stack(int s):N(s){}

		// isEmpty
		bool isEmpty()
		{
			return first == nullptr;
		}
		size_t size()
		{
			return N;
		}

		// push()
		void push(data_t d)
		{
			temp = new Node<data_t>();
			temp->item = d;
			temp->next = first;
			first = temp;
		}

		// pop();
		data_t pop()
		{
			data_t t = first->item;

			temp = first;
			first = first->next;
			delete temp;
			temp = nullptr;

			return t;
		}

		typename Node<data_t>::NodePtr begin() const {return first;}
		typename Node<data_t>::NodePtr end() const 
		{
			temp = first;
			while(temp->next != nullptr)
				temp = temp->next;

			return temp;
		}

		~Stack();
	private:
		int N; // the size of stack
		typename Node<data_t>::NodePtr first;
		//typename Node<data_t>::NodePtr last;
		typename Node<data_t>::NodePtr temp;
};

template<typename T>
Stack<T>::~Stack()
{
	temp = first;
	while(first != nullptr)
	{
		temp = first->next;
		delete first;
		first = temp;
	}
}

// Queue: FIFO
template <typename T>
class Queue
{
	public:
		typedef T data_t;

		bool isEmpty()
		{
			return first == nullptr;
		}
		size_t size()
		{
			return N;
		}

		void enqueue(data_t d)
		{
			temp = new Node<data_t>();
			temp->item = d;
			if(isEmpty())
				first = temp;
			else
				last->next = temp;
			last = temp;

			N++;
		}

		data_t dequeue()
		{
			data_t t = first->item;
			temp = first;
			first = first->next;
			if(temp != nullptr)
				delete temp;
			temp = nullptr;
			if(isEmpty())
			{
				last = nullptr;
				first = nullptr;
			}

			N--;

			return t;
		}
		
		~Queue();

	private:
		int N = 0;
		typename Node<data_t>::NodePtr first;
		typename Node<data_t>::NodePtr last;
		typename Node<data_t>::NodePtr temp;
};

template <typename T>
Queue<T>::~Queue()
{
	/*
	temp = first;
	while(first != last)
	{
		temp = first->next;
		if(first != nullptr)
			delete first;
		first = temp;
	}
	if(last != nullptr)
		delete last;
	*/
}


int main(int argc, char **argv)
{
	cout << "hello world " << endl;

	Stack<int> sta(5);
	sta.push(1);
	cout << sta.pop() << endl;

	Queue<int> que;
	que.enqueue(1);
	que.enqueue(2);
	cout << "queue's size = " << que.size() << endl;
	cout << que.dequeue() << endl;

	return 0;
}

