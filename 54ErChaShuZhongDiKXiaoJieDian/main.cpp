/**
 * @author smh
 * @date 2018.08.18
 * 
 * @brief 剑指offer第54题
 *   二叉搜索树的第k小节点
 *
 *   思路：
 *      1. 二叉搜索树，其中序遍历就是从小到达的顺序排列的，因此按照中序遍历中的第k个数即为所求
 */
#include <iostream>

using namespace std;

class BinaryTree
{
public:
    int data;
    BinaryTree *leftNode;
    BinaryTree *rightNode;
};

// 中序遍历：先左节点、在根节点、最后右节点
BinaryTree* getKthNodeCore(BinaryTree* pRoot, int &k)
{
    BinaryTree* target = nullptr;

    // 先最左侧节点
    if(pRoot->leftNode != nullptr)
        target = getKthNodeCore(pRoot->leftNode, k);

    // 判断本层递归的根节点
    if(target == nullptr)
    {
        if(k == 1)    // 如果k != 1,那么target仍是 nullptr
            target = pRoot;
        --k;
    }

    if(target == nullptr && pRoot->rightNode != nullptr)
        target = getKthNodeCore(pRoot->rightNode, k);

    return target;
}

BinaryTree* getKthNode(BinaryTree* pRoot, int k)
{
    if (pRoot == nullptr || k == 0)
        return nullptr;

    return getKthNodeCore(pRoot, k);
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    // To Be Tested

    return 0;
}