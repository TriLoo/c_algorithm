/**
 * \author smh
 * \date 2018.08.03
 *
 * \brief 剑指offer第24题
 *
 * \brief 思路
 *          1. 定义三个临时变量，分别指向当前元素、上一个元素、下一个元素
 */
#include <iostream>

struct Node
{
    Node(int a = 0):data_(a), pnext_(nullptr){}
    int data_;
    Node * pnext_;
};

enum {
    kValid = 1,
    kInValid
};

int g_status = kValid;   // 用于保存全局状态

/**
 * \class Lists 链表
 * \brief 支持查看倒数第k个节点的链表, 支持判断是否存在环以及环的入口节点等
 */
class Lists
{
public:
    Lists(): pRoot_(nullptr){}

    void add(int a)
    {
        Node * n = new Node(a);
        if (pRoot_ == nullptr)
        {
            pRoot_ = n;
            return;
        }
        Node *pcurr = pRoot_;
        while (pcurr->pnext_ != nullptr)
            pcurr = pcurr->pnext_;
        pcurr->pnext_ = n;
    }

    void clear()
    {
        if (pRoot_ == nullptr)
            return;
        Node *pcurr = pRoot_;
        Node *pHead = pcurr->pnext_;
        while(pcurr != nullptr)
        {
            delete pcurr;
            pcurr = pHead;
            if (pHead != nullptr)
                pHead = pHead->pnext_;
            else
                break;
        }
    }

    Node* meetingNode();

    Node* ReverseNode();

    int kthNode(int k)
    {
        if (pRoot_ == nullptr)
        {
            g_status = kInValid;
            return -1;
        }

        Node *prev = pRoot_, *plast = pRoot_;
        for (int i = 0; i < k; ++i)
        {
            if (plast != nullptr)
                plast = plast->pnext_;
            else
            {
                g_status = kInValid;
                return -1;
            }
        }
        while (plast != nullptr)      // 从倒数一开始计数
        {
            plast = plast->pnext_;
            prev = prev->pnext_;
        }

        return prev->data_;
    }

    Node* entryNode();

private:
    Node* pRoot_;
};

Node* Lists::meetingNode()
{
    if (pRoot_ == nullptr)
        return nullptr;

    Node * prev = pRoot_;
    Node * latter = pRoot_->pnext_;
    if (latter == nullptr)
        return nullptr;

    // 每次对指针进行取值之前都需要判断是否是空指针
    // 先判断是否相等，然后再更新两个指针
    while (latter != nullptr && prev != nullptr)
    {
        if (prev == latter)
            return prev;

        prev = prev->pnext_;

        latter = latter->pnext_;
        if (latter != nullptr)
            latter = latter->pnext_;
    }

    return nullptr;
}

Node* Lists::entryNode()
{
    Node *mNode = meetingNode();

    int nInLoop = 0;
    Node *pTemp = mNode;
    if (pTemp != nullptr)
        pTemp = pTemp->pnext_;
    else
        return nullptr;   // 不存在环

    while (pTemp != nullptr && pTemp != mNode)
    {
        pTemp = pTemp->pnext_;
        ++nInLoop;
    }

    pTemp = pRoot_;
    Node *pNext = pRoot_;
    for (int i = 0; i < nInLoop; ++i)
        pNext = pNext->pnext_;

    while (pTemp != pNext)
    {
        pTemp = pTemp->pnext_;
        pNext = pNext->pnext_;
    }
}

Node* Lists::ReverseNode()
{
    if(pRoot_ == nullptr)
        return nullptr;

    Node* plast = pRoot_;
    Node* pcurr = pRoot_->pnext_;
    Node* pnext = nullptr;
    if (pcurr != nullptr)
        pnext = pcurr->pnext_;

    while (pcurr != nullptr)
    {
        pcurr->pnext_ = plast;
        plast = pcurr;
        pcurr = pnext;
        if (pcurr != nullptr)
            pnext = pcurr->pnext_;
    }

    return plast;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    // TO BE TESTED

    return 0;
}
