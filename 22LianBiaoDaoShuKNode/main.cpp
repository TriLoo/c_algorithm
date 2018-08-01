/**
 * \author smh
 * \date 2018.08.01
 *
 * \brief 剑指Offer第22题
 *
 * \brief 思路
 *          1. 基于两个指针，他们之间相距k个节点，当后面的指针遍历到结尾时，前面的指针刚好是倒数第k个节点
 *          2. 指针操作时，需要特别注意访存的问题以及空指针的问题
 */

#include <iostream>

using namespace std;

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
 * \brief 支持查看倒数第k个节点的链表
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

private:
    Node* pRoot_;
};

int main() {
    //std::cout << "Hello, World!" << std::endl;
    Lists L;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int a;
        cin >> a;
        L.add(a);
    }

    cout << "3 th node: " << endl;
    cout << L.kthNode(3) << endl;
    L.clear();
    cout << "Done." << endl;

    return 0;
}
