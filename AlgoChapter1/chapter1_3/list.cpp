#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename T>
class Node
{
	public:
		typedef T data_t;
		typedef Node<T>* NodePtr;
		data_t item;
		NodePtr next;
};

// main function
int main(int argc, char **argv)
{
	cout << "hello world ..." << endl;

	Node<int>* FirstNode = new Node<int>();
	FirstNode->item = 1;
	FirstNode->next = nullptr;
	Node<int>* SecondNode = new Node<int>();
	SecondNode->item = 2;
	SecondNode->next = nullptr;
	Node<int>* ThirdNode = new Node<int>();
	ThirdNode->item = 3;
	ThirdNode->next = nullptr;

	// construct list
	FirstNode->next = SecondNode;
	SecondNode->next = ThirdNode;

	// Traversal
	Node<int> *ele = FirstNode;
	while(ele != nullptr)
	{
		cout << ele->item << endl;
		ele = ele->next;
	}

	// Add before the first element
	Node<int>* ZeroNode = new Node<int>();
	//Node<int>* OldFirst = FirstNode;
	ZeroNode->item = 0;
	ZeroNode->next = FirstNode;
	FirstNode = ZeroNode;

	cout << "After Add one more element ..." << endl;
	ele = FirstNode;
	while(ele != nullptr)
	{
		cout << ele->item << endl;
		ele = ele->next;
	}

	// add After the last element
	ele = FirstNode;
	while(ele->next != nullptr)
		ele = ele->next;
	Node<int>* FifthNode = new Node<int>();
	FifthNode->item = 5;
	FifthNode->next = nullptr;
	ele->next = FifthNode; 

	cout << "After add one more element after the last element ..." << endl;
	ele = FirstNode;
	while(ele != nullptr)
	{
		cout << ele->item << endl;
		ele = ele->next;
	}

	// delete the Nth element
	int N = 3;
	ele = FirstNode;
	while(ele != nullptr && --N > 1)
		ele = ele->next;
	if(ele == nullptr)
		cout << "The size is smaller ..." << endl;
	else
	{
		Node<int> *del = ele->next;
		ele->next = del->next;
		delete del;
	}

	cout << "After delete the 3th element ..." << endl;
	ele = FirstNode;
	while(ele != nullptr)
	{
		cout << ele->item << endl;
		ele = ele->next;
	}

	// Free the memory
	ele = FirstNode;
	Node<int> *temp = ele;
	while(ele != nullptr)
	{
		temp = ele->next;
		delete ele;
		ele = temp;
	}

	return 0;
}
