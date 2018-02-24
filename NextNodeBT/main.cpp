#include <iostream>
#include <vector>
#include <cassert>
#include <memory>

using namespace std;

struct Node
{
    int Value;
    Node *leftNode, *rightNode, *fatherNode;
};

// Return a point, so that the caller must test the return value equal to nullptr or not
Node* NextNodeValue(Node *node)
{
    if (node == nullptr)
        throw runtime_error("Invalid Node input.");

    Node *pNext = nullptr;

    if (node->rightNode != nullptr)
    {
        Node *pRight = node->rightNode;
        while(pRight->leftNode != nullptr)
            pRight = pRight->leftNode;

        pNext = pRight;
    }
    else if (node->fatherNode != nullptr)
    {
        Node *pCurr = node;
        Node *pParent = node->fatherNode;

        while(pParent != nullptr && pCurr == pParent->rightNode)
        {
            pCurr = pParent;
            pParent = pCurr->fatherNode;
        }

        pNext = pCurr->fatherNode;
    }

    return pNext;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    return 0;
}