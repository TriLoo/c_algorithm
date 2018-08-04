/**
 *  \author smh
 *  \date 2018.08.04
 *
 *  \brief 剑指offer第27题
 *
 *  \brief 思路：
 *              1. 利用递归的思想，按照树的前序遍历，交互其子节点即可
 */
#include <iostream>

using namespace std;

struct BinaryTreeNode
{
    int data;
    BinaryTreeNode* pLeft_;
    BinaryTreeNode* pRight_;
};

void mirrorBinaryTree(BinaryTreeNode* proot)
{
    if (proot == nullptr)
        return ;
    if (proot->pRight_ == nullptr && proot->pLeft_ == nullptr)
        return ;

    BinaryTreeNode* pTemp = proot->pLeft_;
    proot->pLeft_ = proot->pRight_;
    proot->pRight_ = proot->pLeft_;

    if (proot->pLeft_ != nullptr)
        mirrorBinaryTree(proot->pLeft_);
    if (proot->pRight_ != nullptr)
        mirrorBinaryTree(proot->pRight_);
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    // To Be Tested.

    return 0;
}