/**
 * @author smh
 * @date 2018.09.14
 *
 * @brief Minimum Depth of Binary Tree
 *      leetcode 111
 *
 *      Given a binary tree, find its minimum depth. The minimum depth is the number of nodes along the shortest path
 *      from the root node down to the nearest leaf node.
 */
#include <iostream>

using namespace std;

struct BinaryTree
{
    BinaryTree* leftNode;
    BinaryTree* rightNode;

    int data;
};

void getMinimumDepth(BinaryTree* pRoot, int currDepth, int& minDepth)
{
    if(pRoot == nullptr)
    {
        if(currDepth < minDepth)
            minDepth = currDepth;
        return ;
    }

    ++currDepth;
    getMinimumDepth(pRoot->leftNode, currDepth, minDepth);
    getMinimumDepth(pRoot->rightNode, currDepth, minDepth);
}

int getMinimumDepth(BinaryTree* pRoot)
{
    if(pRoot == nullptr)
        return 0;

    int minDepth = 1;
    int currDepth = 1;

    if(pRoot->leftNode != nullptr)
        getMinimumDepth(pRoot->leftNode, currDepth, minDepth);

    if(pRoot->rightNode != nullptr)
        getMinimumDepth(pRoot->rightNode, currDepth, minDepth);

    return minDepth;
}

int main() {
    // Under test

    return 0;
}
