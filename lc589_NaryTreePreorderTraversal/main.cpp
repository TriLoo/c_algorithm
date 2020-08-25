/**
 * \brief lc589 N-ary Tree Preorder Traversal
 * 
 *  level Easy.
 *  Given an n-ary tree, return the preorder traversal of its nodes' value.
 *  Not use a recursive solution, but do it iteratively.
 * 
 * \file main.cpp
 * \date 2020.08.25
 */

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

class Node
{
public:
    int val;
    vector<Node*> children;
    Node(int _val) : val(_val) {}
    Node(int _val, vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    /// solution 1: use queue to do the preorder traversal, FILO
    vector<int> preorder(Node* root) 
    {
        if (root == nullptr)
            return {};

        stack<Node *> tree_queue;
        vector<int> res;
        tree_queue.push(root);

        while(tree_queue.size())
        {
            // auto curr = tree_queue.front();
            auto curr = tree_queue.top();
            tree_queue.pop();
            if (curr == nullptr)
                continue;
            res.push_back(curr->val);
            for(auto beg = curr->children.rbegin(); beg != curr->children.rend(); ++beg)
                tree_queue.push(*beg);
        }

        return res;
    }
};

int main()
{
    return 0;
}