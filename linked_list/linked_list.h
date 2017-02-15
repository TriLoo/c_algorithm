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
#endif
