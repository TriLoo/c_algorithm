#include <iostream>
#include "vector"
#include "memory"

using namespace std;
//using namespace cv;

class BTreeNode
{
public:
    BTreeNode(int v):value_(v){}
    typedef shared_ptr<BTreeNode> Ptr;
    Ptr leftNode_, rightNode_;

    int value_;
private:

};

// 中序需要递增
bool isSorted(shared_ptr<BTreeNode> node)
{
    if (node == nullptr)
        return true;

    int valMid, valLeft, valRight;
    bool ret = true;
    valMid = node->value_;
    if (node->leftNode_ != nullptr && ret)
    {
        valLeft = node->leftNode_->value_;
        if (valLeft <= valMid)
            ret = isSorted(node->leftNode_);
        else
            return false;
    }
    if (node->rightNode_ != nullptr && ret)
    {
        valRight = node->rightNode_->value_;
        if (valMid < valRight)
            ret = isSorted(node->rightNode_);
        else
            return false;
    }

    return ret;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    shared_ptr<BTreeNode> btn = make_shared<BTreeNode>(10);
    btn->rightNode_ = make_shared<BTreeNode>(11);
    btn->leftNode_ = make_shared<BTreeNode>(9);
    btn->leftNode_->leftNode_ = make_shared<BTreeNode>(12); // Not a Binary Tree

    cout << isSorted(btn) << endl;

    return 0;
}
