/**
 * @author smh
 * @date 2018.08.18
 *
 * @brief 剑指offer第55题
 *   二叉树的深度
 *
 *   思路：
 *      1. 动态规划，本层递归的深度为其左子树深度和右子树中深度最大的一路+1
 */
#include <iostream>

using namespace std;

class BinaryTree
{
public:
    int data;
    BinaryTree* leftNode;
    BinaryTree* rightNode;
};


int constructDepth(BinaryTree* pRoot)
{
    if(pRoot == nullptr)
        return 0;

    int leftDepth = constructDepth(pRoot->leftNode);
    int rightDepth = constructDepth(pRoot->rightNode);

    return (leftDepth > rightDepth) ? (leftDepth+1) : (rightDepth + 1);
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    // Under Test

    return 0;
}
