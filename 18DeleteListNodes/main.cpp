#include <iostream>

using namespace std;

struct Node
{
    Node(int a):data(a), p_next(nullptr){}

    int data;
    Node* p_next;
};

class Lists
{
public:
    Lists():phead(nullptr){}

    void addNode(Node *a);
    void deleteNode(Node *a);

    void printList();

private:
    Node *phead;
};

void Lists::addNode(Node *a)
{
    if (a == nullptr)
        return;

    // set the head ptr
    if (phead == nullptr)
    {
        phead = a;
        return;
    }

    // add new node
    Node* pcurr = phead;
    while(pcurr->p_next != nullptr)
        pcurr = pcurr->p_next;
    pcurr->p_next = a;
}

void Lists::deleteNode(Node *a)
{
    // 判断输入以及链表是否合格
    if (a == nullptr || phead == nullptr)
        return;

    // a is the head ptr
    if(a == phead)
    {
        phead = phead->p_next;
        delete a;
        return;
    }

    // a is the tail ptr
    if (a->p_next == nullptr)
    {
        Node *pcurr = phead;
        while(pcurr->p_next->p_next != nullptr)
            pcurr = pcurr->p_next;
        pcurr->p_next = nullptr;
        delete a;
        return;
    }

    // a is the middle
    a->data = a->p_next->data;
    Node *temp = a->p_next;
    a->p_next = a->p_next->p_next;
    //delete temp;   // or default called when leaving this function
}

void Lists::printList()
{
    Node* pcurr = phead;
    while(pcurr != nullptr)
    {
        cout << pcurr->data;
        pcurr = pcurr->p_next;
    }
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    // for test
    Lists t;
    Node *a = new Node(1);
    Node *b = new Node(2);
    Node *c = new Node(3);
    t.addNode(a);
    t.addNode(b);
    t.addNode(c);
    cout << "Before delete:" << endl;
    t.printList();
    cout << endl;

    cout << "After delete:" << endl;
    t.deleteNode(b);
    t.printList();
    cout << endl;
    cout << "After delete head:" << endl;
    t.deleteNode(a);
    t.printList();
    cout << endl;
    cout << "After delete last node:" << endl;
    t.deleteNode(b);   // Note: the last node is in the origin 'b' node ! ! !
    t.printList();
    cout << endl;

    return 0;
}
