/**
 * \brief lc104 Maximum Depth of Binary Tree
 * 
 *  level Easy.
 *  Given a binary tree, find its maximum depth.
 * 
 * \file main.cpp
 * \date 2020.08.26
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return std::max(root->left, root->right) + 1;
    }

};

int main()
{
    return 0;
}