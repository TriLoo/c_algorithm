#include <iostream>
#include "vector"
#include "cassert"
#include "memory"

using namespace std;

struct Node
{
    Node(int a = 0)
    {
        value = a;
    }

    int value = 0;
    int Num = 0;

    shared_ptr<Node> next = nullptr;
};

void addNode(shared_ptr<Node> &Head, int node)
{
    (Head->Num)++;

    shared_ptr<Node> pre = Head;
    shared_ptr<Node> post = Head->next;

    if (Head->Num == 1)
    {
        Head->value = node;
        return;
    }

    while(post != nullptr)
    {
        pre = post;
        post = post->next;
    }
    assert(pre != nullptr);
    pre->next = make_shared<Node>(node);
}

bool isInList(shared_ptr<Node> head, int val)
{
    while(head != nullptr)
    {
        if(head->value == val)
            return true;
        head = head->next;
    }
    return false;
}

bool isWhite(vector<shared_ptr<Node> > &list, int ith)
{
    shared_ptr<Node> head = list[ith];
    int a = ith;
    int b = head->value;
    int c = head->next->value;

    //cout << a << " " << b << " " << c << endl;

    if (isInList(list[b], c))
        return true;
    else
        return false;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    int n, m;

    cin >> n >> m;

    vector<shared_ptr<Node> > Lists(n, nullptr);

    //cout << n << " " << m;

    for (int i = 0; i < n; ++i)
        Lists[i] = make_shared<Node>();

    int a, b;
    for (int i = 0; i < n; ++i)
    {
        cin >> a >> b;
        addNode(Lists[a-1], b-1);
        addNode(Lists[b-1], a-1);
        //cout << a << " " << b;
    }

    for (int i = 0; i < n; ++i)
    {
        int numT = Lists[i]->Num;
        //cout << "NumT = " << numT << endl;
        if (numT == 2 || numT == 3)
        {
            if (isWhite(Lists, i))
            {
                cout << 1 << endl;
                return 1;
            }
        }
    }

    cout << 0 << endl;

    return 0;
}
