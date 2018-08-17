/**
 * @author smh
 * @date 2018.08.17
 *
 * @brief 剑指offer第34题
 *   二叉树中和为某一值的路径
 *
 *   思路：
 *      1. 前序遍历二叉树
 *      2. 递归调用遍历二叉树的节点，先进后出，直到遍历完所有的节点
 *
 */
#include <iostream>
#include <vector>

using namespace std;

class BinaryTree
{
public:
    int data_;
    BinaryTree* leftNode_;
    BinaryTree* rightNode_;
};

void getPath(BinaryTree* pRoot, int expSum)
{
    if (pRoot == nullptr)
        return;
    int currSum = 0;
    vector<int> paths;
    getPath(pRoot, paths, currSum, expSum);
}

void getPath(BinaryTree* pRoot, vector<int>& paths, int & currSum, int expSum)
{
    if (pRoot == nullptr)
        return;
    currSum += pRoot->data_;
    paths.push_back(pRoot->data_);

    if (currSum == expSum && (pRoot->leftNode_ == nullptr) && (pRoot->rightNode_ == nullptr))
    {
        cout << "Path found!" << endl;
        for (auto ele : paths)
            cout << ele << " ";
        cout << endl;
    }

    if (pRoot->leftNode_ != nullptr)
        getPath(pRoot->leftNode_, paths, currSum, expSum);
    if (pRoot->rightNode_ != nullptr)
        getPath(pRoot->rightNode_, paths, currSum, expSum);

    paths.pop_back();
}

int main() {

    // Under Test

    return 0;
}

