/**
 * \brief lc144 Binary Tree Preorder Traversal
 * 
 *  level Medium.
 *  Given a binary tree, return the preorder of its nodes' value.
 *  Implement it iteratively instead of recursive solution.
 * 
 * \file main.cpp
 * \date 2020.08.25
 */

#include <vector>
#include <iostream>
#include <stack>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return {};

        vector<int> res;
        stack<TreeNode*> tree_stack;
        tree_stack.push(root);

        while(tree_stack.size())
        {
            auto curr = tree_stack.top();
            tree_stack.pop();
            res.push_back(curr->val);
            if (curr->right)
                tree_stack.push(curr->right);
            if (curr->left)
                tree_stack.push(curr->left);
        }

        return res;
    }
};

int main()
{
    return 0;
}
