/**
 * @author smh
 * @date 2018.08.21
 *
 * @brief 剑指offer第32题
 *   分行从上到下打印二叉树
 *
 *   思路：
 *      1. 分层的话可以通过队列实现，即广度优先遍历；为了分行，需要记录当前层的节点的个数，以及下一层的节点的个数，然后每次需要更新
 */
#include <iostream>
#include <queue>

using namespace std;

struct BinaryTree
{
    int data;
    BinaryTree* leftNode;
    BinaryTree* rightNode;
};

void printBinaryTreeLayers(BinaryTree* pRoot)
{
    if (pRoot == nullptr)
        return ;

    deque<BinaryTree *>  nodeQueue;
    nodeQueue.push_back(pRoot);
    int currLayer = 1;
    int nextLayer = 0;
    while (nodeQueue.size() != 0)
    {
        BinaryTree* pTemp = nodeQueue.back();
        cout << pTemp->data << " ";
        if (pTemp->leftNode != nullptr)
        {
            nodeQueue.push_back(pRoot->leftNode);
            ++nextLayer;
        }
        if (pTemp->rightNode != nullptr)
        {
            nodeQueue.push_back(pRoot->rightNode);
            ++nextLayer;
        }
        cout << pTemp->data << " ";
        --currLayer;
        nodeQueue.pop_back();
        if(currLayer == 0)
        {
            cout << endl;
            currLayer = nextLayer;
            nextLayer = 0;
        }
    }
}


int main() {
    //std::cout << "Hello, World!" << std::endl;

    return 0;
}
