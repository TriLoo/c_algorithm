#include <iostream>

using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL){}
};

class Solution
{
	public:
	ListNode * addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode* lhsTemp = l1;
		ListNode* rhsTemp = l2;

		int rhsCount = 0;
		int lhsCount = 0;

		int flag = 0;

		// calculate the length of two input list
		while(lhsTemp != nullptr)
		{
			lhsCount++;
			lhsTemp = lhsTemp->next;
		}
		while(rhsTemp != nullptr)
		{
			rhsCount++;
			rhsTemp = rhsTemp->next;
		}

		//int Count = max(rhsCount, lhsCount);
		int Count = rhsCount < lhsCount ? rhsCount : lhsCount;
		int tempSum = 0;

		if(Count == rhsCount)  // return the lhs
		{
			lhsTemp = l1;
			rhsTemp = l2;
			for(int i = 0; i < Count; i++)
			{
				lhsTemp->val += rhsTemp->val + flag;
				flag = lhsTemp->val / 10;
				lhsTemp->val %= 10;
				lhsTemp = lhsTemp->next;
				rhsTemp = rhsTemp->next;
			}

			for(int i = Count; i < lhsCount; ++i)
			{
				lhsTemp->val += flag;
				flag = lhsTemp->val / 10;
				lhsTemp->val %= 10;
				lhsTemp = lhsTemp->next;
			}

			if(flag == 1)
			{
				ListNode *temp = new ListNode(flag);
				//ListNode temp(flag);
				lhsTemp = l1;
				for(int i = 0; i < Count - 1; i++)
				{
					lhsTemp = lhsTemp->next;
				}
				lhsTemp->next = temp;
				//lhsTemp->next->val = flag;
			}

			return l1;
		}
		else                     // return the rhs
		{
			lhsTemp = l1;
			rhsTemp = l2;
			for(int i = 0; i < Count; i++)
			{
				rhsTemp->val += lhsTemp->val + flag;
				flag = rhsTemp->val / 10;
				rhsTemp->val %= 10;
				lhsTemp = lhsTemp->next;
				rhsTemp = rhsTemp->next;
			}

			for(int i = Count; i < rhsCount; ++i)
			{
				rhsTemp->val += flag;
				flag = rhsTemp->val / 10;
				rhsTemp->val %= 10;
				rhsTemp = rhsTemp->next;
			}

			return l2;
		}
	}
};

int main()
{

	/*
	ListNode lhs(0);
	ListNode rhs(7);
	ListNode rhs2(3);
	rhs.next = &rhs2;
	rhs.next->val = 3;
	*/
	ListNode lhs(5);
	ListNode rhs(5);
	ListNode *Result;

	Solution S;
	Result = S.addTwoNumbers(&lhs, &rhs);

	cout << Result->val << endl;

	return 0;
}
