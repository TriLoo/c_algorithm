#include <iostream>
#include <vector>
#include "memory"
#include "cassert"

using namespace std;

struct Node
{
    int Value;
    shared_ptr<Node> leftNode, rightNode;
};

shared_ptr<Node> Construct(vector<int> pre, vector<int> mid);

shared_ptr<Node> ConsturctBT(vector<int> pre, vector<int> mid)
{
    if (pre.size() == 0 || mid.size() == 0)
        return nullptr;
    else
        return Construct(pre, mid);
}

shared_ptr<Node> Construct(vector<int> pre, vector<int> mid)
{
    if (pre.size() == 0 || mid.size() == 0)
        return nullptr;

    shared_ptr<Node> root = make_shared<Node>();
    root->rightNode = nullptr;
    root->leftNode = nullptr;
    // Or do the assignment here
    // root->Value = pre[0];

    int cnt = 0;
    while(mid[cnt++] != pre[0]);

    cout << "cnt = " << cnt << endl;
    //if (cnt == 1 && root->Value != mid[0])
        //throw runtime_error("Invalid value.");

    if (cnt >= 1)
    {
        root->Value = pre[0];
        root->leftNode = Construct(vector<int>(pre.begin() + 1, pre.begin() + cnt), vector<int>(mid.begin(), mid.begin() + cnt - 1));
    }

    if (cnt < pre.size())
    {
        root->Value = pre[0];
        root->rightNode = Construct(vector<int>(pre.begin() + cnt, pre.end()), vector<int>(mid.begin() + cnt, mid.end()));
    }

    return root;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    vector<int> preOrder{1, 2, 4, 7, 3, 5, 6, 8};
    vector<int> midOrder{4, 7, 2, 1, 5, 3, 8, 6};

    shared_ptr<Node> head = ConsturctBT(preOrder, midOrder);

    cout << "Size = " << preOrder.end() - preOrder.begin() << endl;
    /*
    vector<int> temp;
    temp = vector<int>(preOrder.begin(), preOrder.end());
    cout << "Test Size = " << temp.size() << endl;
    for (auto ele : temp)
        cout << ele << endl;
    */

    return 0;
}
