/**
 * \author smh
 * \date 2018.08.03
 *
 * \brief 剑指offer第25题
 *
 * \brief 思路
 *          1. 其实就是合并排序的过程, 这里是从小到大
 *          2. 需要注意的是，现在操作的是链表，也就是指针比较多
 *          3. 可以基于递归的思想来做
 */

#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* pNext_;
};

Node* mergeLists(Node* pLst, Node *pRst)
{
    if (pLst == nullptr)
        return pRst;
    else if (pRst == nullptr)
        return pLst;

    Node *pHead = nullptr;
    if (pLst->data < pRst->data)
    {
        pHead = pLst;
        pHead->pNext_ = mergeLists(pLst->pNext_, pRst);
    }
    else
    {
        pHead = pRst;
        pHead->pNext_ = mergeLists(pLst, pRst->pNext_);
    }

    return pHead;
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    return 0;
}
