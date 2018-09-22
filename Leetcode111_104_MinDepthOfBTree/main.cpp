/**
 * @author smh
 * @date 2018.09.14
 *
 * @brief Minimum Depth of Binary Tree
 *      leetcode 111, 104
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

// 动态规划 + 栈(后进先出): 根节点处的最小深度等于其左右最小深度加一
int getMinimumDepth(BinaryTree* pRoot)
{
    if(pRoot == nullptr)
        return 0;
    int L = getMinimumDepth(pRoot->leftNode);
    int R = getMinimumDepth(pRoot->rightNode);

    return 1 + ((L && R) ? min(L, R) : max(L, R));
}

int getMaximumDepth(BinaryTree* pRoot)
{
    if(pRoot == nullptr)
        return 0;

    int L = getMaximumDepth(pRoot->leftNode);
    int R = getMaximumDepth(pRoot->rightNode);

    return 1 + max(L, R);
}

int main() {
    // Under test

    return 0;
}
