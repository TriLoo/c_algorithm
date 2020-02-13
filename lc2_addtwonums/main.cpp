/**
 *  \brief lc2 Add Two Numbers
 * 
 *  medium level
 *  You are given two non-empty linked lists representing two non-negative integers. The digits are stored in 
 *    reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 *  You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *  
 *  \author smh
 *  \date 2020.02.13
 */
#include <iostream>

using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

// baseline: 24 ms, 12 MB
class Solution{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(0);
        ListNode* curr = head;
        int c = 0;
        while(l1 != nullptr || l2 != nullptr)
        {
            int a = 0, b = 0;
            if (l1 != nullptr)
            {
                a = l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr)
            {
                b = l2->val;
                l2 = l2->next;
            }
            int s = a + b + c;
            c = s / 10;
            s = s % 10;

            ListNode* curr_node = new ListNode(s);
            curr->next = curr_node;
            curr = curr->next;
        }

        // process additional carry bit
        if (c != 0)
            curr->next = new ListNode(c);

        return head->next;
    }
};

// for memory reduce! Not work good, 28 ms, 11.9 MB
class Solution2{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int c = 0;
        ListNode* head = new ListNode(0);
        ListNode* curr = head;
        while(l1 != nullptr || l2 != nullptr || c != 0)
        {
            int s = c + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
            c = s / 10;
            curr->next = new ListNode(s % 10);
            curr = curr->next;
        }

        return head->next;
    }
};

int main()
{
    return 0;
}
