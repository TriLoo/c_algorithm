#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

struct node;
typedef struct node* ptrToList;

struct node 
{
	int num;
	ptrToList next;
};

ptrToList MakeEmpty(ptrToList L);
int IsEmpty(ptrToList L);
int IsLast(ptrToList L);
ptrToList Find(int x, ptrToList L);


#endif
