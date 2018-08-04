/**
 * \author smh
 * @date 2018.08.04
 *
 * @brief 剑指offer第28题
 *
 * @brief 思路
 *          1. 定义一个新的遍历树的方式：前序遍历时，先根节点、在右节点，最后才是坐节点。如果是镜像的
 *          2. 在遍历的时候，需要考虑nullptr
 */
#include <iostream>
#include <list>

using namespace std;

struct BinaryTreeNode
{
    int data;
    BinaryTreeNode* pLeft_;
    BinaryTreeNode* pRight_;
};

bool isMirrored(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    if (pRoot1 == nullptr && pRoot2 == nullptr)
        return false;
    if (pRoot1 == nullptr || pRoot2 == nullptr)
        return false;

    if (pRoot1->data != pRoot2->data)
        return false;

    return isMirrored(pRoot1->pRight_, pRoot2->pLeft_) && isMirrored(pRoot1->pLeft_, pRoot2->pRight_);   // 在这里，递归的时候等价于遍历的顺序是不同的
}


bool isMirrored(BinaryTreeNode* pRoot)
{
    if (pRoot == nullptr)
        return false;

    return isMirrored(pRoot, pRoot);
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    return 0;
}
