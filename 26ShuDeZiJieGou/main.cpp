/**
 * \author smh
 * \date 2018.08.03
 *
 * \brief 剑指Offer第26题
 *
 * \brief 思路：
 *          1. 分成两步来做：首先判断跟节点是否相同，然后判断它们的子节点是相同的
 *          2. 中序遍历根节点
 */
#include <iostream>

using namespace std;

struct BinaryTreeNode
{
    int data;          // 注意这里是整形，如果是浮点数，其判断相等时需要额外的小心
    BinaryTreeNode* pLeft_ = nullptr;
    BinaryTreeNode* pRight_ = nullptr;
};

bool isEqual(BinaryTreeNode* plst, BinaryTreeNode* prst)
{
    if (plst == nullptr && prst != nullptr)
        return false;
    if (plst == nullptr && prst == nullptr)
        return true;

    if (plst->data == prst->data)
    {
        if (plst != nullptr || prst != nullptr)
        {
            isEqual(plst->pRight_, prst->pRight_);
            isEqual(plst->pLeft_, prst->pLeft_);
        }
    }
    else
        return false;
}

/**
 * \brief 两层递归来实现判断是否相等
 *
 * @param pLst
 * @param pRst
 * @return
 */
bool isContained(BinaryTreeNode* pLst, BinaryTreeNode* pRst)
{
    if (pLst == nullptr || pRst == nullptr)
        return false;

    bool result = false;

    if (pLst->data == pRst->data)
        result = isEqual(pLst, pRst);

    if (!result)
        result = isContained(pLst->pLeft_, pRst->pLeft_);

    if (!result)
        result = isContained(pLst->pRight_, pRst->pRight_);

    return result;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    return 0;
}
